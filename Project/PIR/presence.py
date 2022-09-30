#!/usr/bin/env python
# coding: utf-8

# ### D1_mini + Raspberry Pi

# In[ ]:


# pip install flask 


# In[ ]:


import sqlite3, datetime, time, queue, threading, sys, os, pathlib, json, flask, io 
import numpy as np, pandas as pd, matplotlib.pyplot as plt 
from dateutil import tz
TZ_NY = tz.gettz('America/New_York')

pathlib.Path('log').mkdir(parents=True, exist_ok=True)
new_db = f'log/presence.{datetime.datetime.now().astimezone(TZ_NY).strftime("%Y%m%d_%H%M%S")}.db' 
new_db = 'log/presence.20220930_010112.db'
def database(): 
    con = sqlite3.connect(new_db)   
    cur = con.cursor() 
    cur.execute('CREATE TABLE IF NOT EXISTS presence (Photoresistor INTEGER, timestamp REAL);')
    cur = con.cursor() 
    while True: 
        opt, foo = q_in.get() # q.get() = opt_foo
        bar = False           # opt is a placeholder 
        try:
            if opt == 'insert':
                cur.execute('INSERT INTO presence VALUES (?, ?);', ( foo['A'], time.time(),))  
            elif opt == 'sql':
                cur.execute(foo)  
                bar = cur.fetchall()
            elif opt == 'commit': 
                con.commit() 
                bar = 'Database commited'
                print('Database commited')
            elif opt == 'close': 
                con.commit()
                con.close()
                bar = 'Database commited and closed'
                print('Database commited and closed')
        except Exception as e:
            print(f'[sql_exception] error: {e}, opt: {opt}, foo: {foo}')
            pass
        q_out.put(bar) 
        q_out.join()
        q_in.task_done()

q_in, q_out = queue.Queue(), queue.Queue() 
threading.Thread(target=database, name='thread-1', daemon=True).start() 

def database_operator(opt_foo): 
    q_in.join()        
    q_in.put(opt_foo)  
    bar = q_out.get()  
    q_out.task_done()   
    return bar

#sys.path.append('/var/www/py3_mod') 
app = flask.Flask(__name__)
@app.route("/")
def index():
    return "FrontPage"

@app.route('/pirLog', methods=["POST"])
def pirLog():  
    js = flask.request.json
    if js['B']:
        database_operator(('insert', js)) 
    return "Hello World"

@app.route('/heartbeat', methods=['GET']) 
def heartbeat():
    database_operator(('commit', None))  
    return 'Cheers!' 

@app.route('/hist', methods=['GET']) 
def hist():
    data = database_operator(('sql', 'select timestamp from presence'))
    if data:
        fig, ax = plt.subplots(figsize=[6, 6])  
        ax.set_xlim(0,24)
        ax.set_xticks(range(24))
        df = pd.DataFrame(data, columns=['timestamp']) 
        df['hour'] = df.apply(lambda x: datetime.datetime.fromtimestamp(x['timestamp']).astimezone(TZ_NY).hour, axis=1) 
        df['hour'].plot(kind='hist', bins=range(24), ax=ax)  
        #plt.gca().set_position([0, 0, 1, 1])
        bio = io.BytesIO()
        plt.savefig(bio,format='svg')
        return bio.getvalue().decode()
    else:
        return "Hist is not ready"

if __name__ == "__main__": 
    import logging 
    werkzeug_logger = logging.getLogger('werkzeug')
    werkzeug_logger.setLevel(logging.DEBUG)
    
    logFormatStr = '%(message)s' 
    formatter = logging.Formatter(logFormatStr,'%m-%d %H:%M:%S')
    fileHandler = logging.FileHandler("log/WARNING.log")
    fileHandler.setLevel(logging.WARNING)
    fileHandler.setFormatter(formatter) 
    werkzeug_logger.addHandler(fileHandler)
    werkzeug_logger.info("Logging is set up.") 
      
    streamHandler = logging.StreamHandler()
    streamHandler.setLevel(logging.DEBUG)
    streamHandler.setFormatter(formatter)
    werkzeug_logger.addHandler(streamHandler)
    
    app.run("0.0.0.0",5009)  


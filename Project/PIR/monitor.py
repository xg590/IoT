#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import multiprocessing, subprocess, requests, time, datetime

def foo(conn): 
    sp = subprocess.Popen(args=['python3','presence.py']) # cannot terminate in main process
    conn.recv()
    conn.close()
    sp.terminate() # Terminate subprocess will put it in zombie state. End its parent process is needed.

heartbeat = 60

while 1:
    pconn, conn = multiprocessing.Pipe()
    p = multiprocessing.Process(target=foo, args=(conn,))
    p.start()
    time.sleep(10)
    while 1:
        try:
            r = requests.get('http://localhost:5009/heartbeat', timeout=10)
            time.sleep(heartbeat)
        except requests.exceptions.Timeout as e:
            pconn.send(None) # unblock another process
            time.sleep(5)
            p.close()        # end another process 
            print(f"heart stopped @ {datetime.datetime.now().strftime('%Y-%m-%dT%H:%M:%S')}; restart now!")
            break 


# In[1]:


get_ipython().system('jupyter nbconvert --to script presence.ipynb')


# In[2]:


get_ipython().system('jupyter nbconvert --to script monitor.ipynb')


# In[ ]:





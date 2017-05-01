import pandas as pd

dfs={ i : pd.DataFrame.from_csv('GOOD_DATALOG'+str(i)+'.csv',sep=',',\
header=None, index_col=None) for i in range(2)} # n files.
panel=pd.Panel(dfs)
dfs_sum=panel.sum(axis=0)
dfs_sum = dfs_sum/2



print(dfs_sum)
import sys
sys.path.append('/home/analyst02/MyWorkspace/project/AlphaResearch/corr')
from utils import weighted_ic, grp_return, corr1, corr2
import numpy as np
import pandas as pd

x = np.array([1,2,3,4,5], dtype='double')
y = np.array([5,4,3,2,1], dtype='double')

result = corr1(x, y)
print(result)

print('function2')
# x = np.array([[1, 2, 3], [4, 5, 6]], dtype='double')

data = pd.read_parquet('20220805.parquet.gzip')
x = np.array(data.iloc[0:30, :],dtype='double' )
result = corr2(x)
result = np.array(result)
print(result)
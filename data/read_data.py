import pandas as pd  
import numpy as np  
import sys

import matplotlib.pyplot as plt

def proc(argv):

    df = pd.read_csv(  argv[0]  , header=None )

    print(df.head())

    x = df.loc[:,1].values
    y = df.loc[:,3].values


    plt.plot(x,y)
    plt.show()

def main(argv):
    proc(argv)


if __name__ == "__main__":
    main(sys.argv[1:])

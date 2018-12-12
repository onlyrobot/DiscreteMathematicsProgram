# 线性同余法生成均匀伪随机数
last = seed = 31 # 默认种子
constant = 32 # 默认常量
def set_seed(sed): # 设置种子
    global seed
    seed = sed
    global last
    last = sed
def get_rand(): # 获取（0~1）之间的随机数
    global last
    last = (seed * last * 100 + constant) % 100 / 100
    return last
if __name__ == '__main__':
    # set_seed(100)
    for i in range(100):
        print(get_rand(), 'with seed', seed, 'with last', last)

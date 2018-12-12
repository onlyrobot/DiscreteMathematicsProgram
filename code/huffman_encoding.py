# huffman encoding
import heapq
s = input('input the string to be encoded\n')
weight = {}
for c in s:
    if c not in weight.keys():
        weight[c] = 1
    else:
        weight[c] += 1
weight = sorted(weight.items(), key = lambda item : item[1])
class HuffmanTree:
    def __init__(self, left = None, right = None, data = None):
        self.left, self.right, self.data = left, right, data
    def __lt__(self, another):
        return False
    def __repr__(self):
        return str(self.data)
    @classmethod
    def print_tree(cls, root, depth = 0):
        if root is None:
            return
        for i in range(depth):
            print('    ', end = '')
        print(root.data)
        HuffmanTree.print_tree(root.left, depth + 1)
        HuffmanTree.print_tree(root.right, depth + 1)
    @classmethod
    def generate_en_dict(cls, root, en_dict, code = ''):
        if root.data is not None:
            en_dict[root.data] = code
        else:
            HuffmanTree.generate_en_dict(root.left, en_dict, code + '0')
            HuffmanTree.generate_en_dict(root.right, en_dict, code + '1')
heap = []
for i in weight:
    heapq.heappush(heap, (i[1], HuffmanTree(None, None, i[0])))
# print(heap)
while len(heap) != 1:
    node1, node2 = heapq.heappop(heap), heapq.heappop(heap)
    heapq.heappush(heap, (node1[0] + node2[0], HuffmanTree(node1[1], node2[1])))
root = heap[0][1]
# HuffmanTree.print_tree(root)
en_dict = {}
HuffmanTree.generate_en_dict(root, en_dict)
print('the encoding map', en_dict)
print('code after encoding\n', str([en_dict[c] for c in s]))

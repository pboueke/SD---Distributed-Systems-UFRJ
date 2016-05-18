import os

root = os.path.dirname(os.path.abspath(__file__))
files = []
dic = {}

for file in os.listdir(root):
    if file.endswith(".dat"):
        files.append(file)
        
for file in files:
    dic[file] = sum([float(s.strip()) for s in open(file).readlines()])/(sum(1.0 for line in open(file)))
    

f = open('results.txt','w')

for key in dic.keys():
    f.write(key.replace("_", " ").replace(".dat", " ") + str(round(dic[key], 3)) + "\n")
f.close()

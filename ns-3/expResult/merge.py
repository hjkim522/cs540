sizes = ['100', '150', '200', '250', '300', '350', '400', '450', '500']
sizes = ['100']

data = {}

for size in sizes:
	print(size)
	f = open('bestroute-topo-'+size+'.ods', 'r')
	line = f.readline() #skip first line
	line = f.readline()
	while line:
		tokens = line.split() # time node type packets
		node = tokens[1] # node name
		hit = tokens[2] # CacheHits | CacheMisses
		count = tokens[3] # count
		line = f.readline()

for datum in data:
	print(datum)

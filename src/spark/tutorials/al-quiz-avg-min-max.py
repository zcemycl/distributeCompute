from pyspark import SparkConf, SparkContext

conf = SparkConf().setAppName("Quick Average Max Min RDD")
sc = SparkContext.getOrCreate(conf=conf)
rdd = sc.textFile("/opt/spark-data/average_quiz_sample.csv")
print(rdd.collect())
rddorig = rdd.map(lambda x: x.split(','))
rddavg = rddorig.map(lambda x: (x[0], (float(x[2]), 1)))
print(rdd.collect())
rddavg = rddavg.reduceByKey(lambda x,y: (x[0]+y[0], x[1]+y[1]))
rddavg = rddavg.map(lambda x: (x[0], x[1][0]/x[1][1]))
print(rddavg.collect())

rddminmax = rddorig.map(lambda x: (x[0], float(x[2])))
rddmin = rddminmax.reduceByKey(lambda x,y: min(x, y))
print(rddmin.collect())

rddmax = rddminmax.reduceByKey(lambda x,y: max(x, y))
print(rddmax.collect())
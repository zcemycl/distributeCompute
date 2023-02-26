from pyspark import SparkConf, SparkContext

def split_to_number(x):
    return [int(s) for s in x.split(" ")]

conf = SparkConf().setAppName("FlatMap RDD")
sc = SparkContext.getOrCreate(conf=conf)
rdd = sc.textFile("/opt/spark-data/sample.txt")
print(rdd.collect())
rdd2 = rdd.flatMap(split_to_number)
print(rdd2.collect())
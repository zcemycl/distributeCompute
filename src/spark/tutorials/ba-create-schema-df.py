from pyspark import SparkConf, SparkContext
from pyspark.sql import SparkSession
from pyspark.sql.types import StructType, StructField, StringType, IntegerType

# direct from csv to df
schema = StructType([
    StructField("age", IntegerType(), True),
    StructField("gender", StringType(), True),
    StructField("name", StringType(), True),
    StructField("course", StringType(), True),
    StructField("roll", StringType(), True),
    StructField("marks", IntegerType(), True),
    StructField("email", StringType(), True),
])

spark = SparkSession.builder.appName("Create Spark DataFrames").getOrCreate()
df = spark.read.options(
        header='True',
        inferSchema='True',
        delimiter=','
    )\
    .schema(schema)\
    .csv("/opt/spark-data/StudentData.csv")
df.show()

df.printSchema()

# from txt to df
conf = SparkConf().setAppName("RDD")
sc = SparkContext.getOrCreate(conf=conf)
rdd = sc.textFile("/opt/spark-data/StudentData.csv")
headers = rdd.first()
columns = headers.split(',')
rdd = rdd.filter(lambda x: x!=headers).map(lambda x: x.split(','))
rdd = rdd.map(lambda x: [
    int(x[0]), # age
    x[1], # gender
    x[2], # name
    x[3], # course
    int(x[4]), # roll
    int(x[5]), # marks
    x[6] # email
])
df_rdd = spark.createDataFrame(rdd, schema=schema)
df_rdd.show()
df_rdd.printSchema()


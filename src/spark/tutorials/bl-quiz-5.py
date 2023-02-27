from pyspark.sql import SparkSession
from pyspark.sql.functions import col, lit, udf, when
from pyspark.sql.types import DoubleType

spark = SparkSession.builder.appName("Quiz Spark DataFrames 5").getOrCreate()
df = spark.read.options(
        header='True',
        inferSchema='True',
        delimiter=','
    )\
    .csv("/opt/spark-data/OfficeData.csv")

def get_increment(salary, bonus, state):
    res = 0
    if (state == "NY"):
        res = 0.1*salary
        res += 0.05*bonus
    elif (state == "CA"):
        res = 0.12*salary
        res += 0.03*bonus
    return res

GetIncrementUDF = udf(lambda x,y,z: get_increment(x, y, z), DoubleType())
df.withColumn("increment", GetIncrementUDF(df.salary, df.bonus, df.state)).show()
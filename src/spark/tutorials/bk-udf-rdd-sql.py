from pyspark.sql import SparkSession
from pyspark.sql.functions import col, lit, udf
from pyspark.sql.types import StructType, StructField, StringType, IntegerType

spark = SparkSession.builder.appName("UDF RDD SQL Spark DataFrames").getOrCreate()
df = spark.read.options(
        header='True',
        inferSchema='True',
        delimiter=','
    )\
    .csv("/opt/spark-data/OfficeData.csv")

def total_salary(salary, bonus):
    return salary + bonus

totalSalaryUDF = udf(lambda x,y: total_salary(x, y), IntegerType())

df = df.withColumn("total_salary", totalSalaryUDF(df.salary, df.bonus))

df.show()

# rdd
rdd = df.rdd
print(rdd.collect())
print(rdd.filter(lambda x: x['state'] == "NY").collect())

# sql
df.createOrReplaceTempView("Office")
spark.sql("select * from Office where department in ('Sales', 'Marketing')").show()
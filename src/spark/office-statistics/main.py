from pyspark.sql import SparkSession
from pyspark.sql.functions import col, lit, udf, min, max, avg
from pyspark.sql.types import StructType, StructField, StringType, IntegerType

spark = SparkSession.builder.appName("Office Data Project").getOrCreate()
df = spark.read.options(
        header='True',
        inferSchema='True',
        delimiter=','
    )\
    .csv("/opt/spark-data/OfficeDataProject.csv")

print("Total number of employees: ", df.count())
df_departments = df.select("department")
print("Total number of departments: ", df_departments.distinct().count())
print("Department Names: ", df_departments.distinct().show())

print("Total number of employees in each department: ", 
    df.groupBy("department").count().show())
print("Total number of employees in each state: ", 
    df.groupBy("state").count().show())
print("Total number of employees in each state in each department: ", 
    df.groupBy("state", "department").count().show())

print("Min Max salaries in each department: ", 
    df.groupBy("department").agg(
    min("salary").alias("min"),
    max("salary").alias("max")).orderBy(
        col("max").asc(),
        col("min").asc()
    ).show())

avg_bonus = df.filter(df.state=="NY")\
    .agg(avg("bonus")\
    .alias("avg_bonus")).collect()[0].avg_bonus
print("Employee Name in NY Finance with more than avg bonus: ", 
    df.filter(
    (df.state=="NY") &\
    (df.department=="Finance") &\
    (df.bonus > avg_bonus)).select("employee_name").show())

def add_500(age, salary):
    return salary+500 if age>45 else salary
Add_500_UDF = udf(lambda x,y: add_500(x, y), IntegerType())
print("Raise 500 salary to age greater than 45: ",
    df.withColumn("salary", Add_500_UDF(df.age, df.salary)).show())

print("Greater than 45: ", df.filter(df.age>45).show())
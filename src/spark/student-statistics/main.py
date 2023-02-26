from pyspark import SparkConf, SparkContext

conf = SparkConf().setAppName("Student Statistics Project")
sc = SparkContext.getOrCreate(conf=conf)
rdd = sc.textFile("/opt/spark-data/StudentData.csv")

headers = rdd.first()
print("Headers: ", headers)
rdd = rdd.filter(lambda x: x!=headers)
rdd = rdd.map(lambda x: x.split(","))
rdd = rdd.map(lambda x: (
    int(x[0]), # age
    x[1], # gender
    x[2], # name
    x[3], # course
    int(x[4]), # roll
    int(x[5]), # marks
    x[6] # email
))
print("Data: ", rdd.collect())
print("Number of students: ", rdd.count())

rdd_fm_total_marks = rdd.map(lambda x: (x[1], x[5]))
rdd_fm_total_marks = rdd_fm_total_marks.reduceByKey(lambda x,y: x+y)
print("Total Marks by Female and Male: ", rdd_fm_total_marks.collect())

rdd_pass = rdd.map(lambda x: x[5]>=50)
print("Pass and Fail: ", rdd_pass.countByValue())

rdd_course = rdd.map(lambda x: x[3])
print("Total number of students per course: ", rdd_course.countByValue())

rdd_total_marks_per_course = rdd.map(lambda x: (x[3], (x[5], 1)))
rdd_total_marks_per_course = rdd_total_marks_per_course.reduceByKey(
    lambda x,y: (x[0]+y[0], x[1]+y[1])
)
print("Total marks that students have achieved per course: ", 
    rdd_total_marks_per_course\
    .map(lambda x: (x[0], x[1][0]))\
    .collect())

print("Average marks that students have achieved per course: ", 
    rdd_total_marks_per_course\
    .map(lambda x: (x[0], x[1][0]/x[1][1]))\
    .collect())

rdd_minmax_per_course = rdd.map(lambda x: (x[3], x[5]))
rdd_min_per_course = rdd_minmax_per_course.reduceByKey(lambda x,y: min(x,y))
print("Min marks per course: ", rdd_min_per_course.collect())

rdd_max_per_course = rdd_minmax_per_course.reduceByKey(lambda x,y: max(x,y))
print("Max marks per course: ", rdd_max_per_course.collect())

rdd_fm_avg_age = rdd.map(lambda x: (x[1], (x[0], 1)))
rdd_fm_avg_age = rdd_fm_avg_age.reduceByKey(
    lambda x,y: (x[0]+y[0], x[1]+y[1])
)
rdd_fm_avg_age = rdd_fm_avg_age.map(lambda x: (x[0], x[1][0]/x[1][1]))
print("Average age of male and female: ", rdd_fm_avg_age.collect())
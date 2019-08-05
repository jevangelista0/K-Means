# K-Means
K-means Clustering assigns a label to each point and helps the program know how to group the labels using a series of calculations.

Kmeans_image_data1.txt -> image in binary.
Kmeans_image_data2.txt -> image in binary.
out1.txt -> each entry is a point in the 2 dimentional matrix.
out2.txt -> the step by step iteration of grouping the labels.
out3.txt -> each entry after the header (first two lines) are the x coordinate, y coordinate and the label.

Try Me:
  - git clone https://github.com/jevangelista0/K-Means.git
  - cd K-Means
  - g++ -std=c++11 Kmeans.cpp
  - a.exe Kmeans_image_data1.txt 4 out1.txt out2.txt out3.txt
      (3rd argument (number) is the number of clusters, 4 for data1 and 6 for data2)
  - type out2.txt (to see output)

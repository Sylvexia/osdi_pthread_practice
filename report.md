# OSDI Midterm Project

HW_5: Using pthread to calculate pi

Name/ID: 洪_鈞/612410065

## What Does the Program Do?

It calculate pi upper bound and lower bound by calculate the area of quarter circle area. The way it calculate the area is simply divide the area to several rectangle verticle to the x-axis.

There are 3 program in this project: ```no_thread```, ```naive_thread```, ```openmp```.

- no_thread.c (Calculating pi with no thread)
- naive_thread.c (Calculating pi with the threading model that I designed)
- openmp.c (Parallized by openmp)

You can specify thread number with ```-t``` and specify the division number with ```-n```

The sample input and output:

```
# input:
./no_thread -n 10
```

```
# output:
Number of division: 10
upper pi_value: 3.304518326248318
lower pi_value: 2.904518326248318
```

```
# input:
./naive_thread -t 16 -n 10000000000
```

```
Number of available CPU: 16
Number of running CPU: 16
Number of division: 10000000000
upper pi_value: 3.141592653789842
lower pi_value: 3.141592653389843
```

To build it, simply using cmake to build it.

For example:

```
mkdir build
cd build
cmake ..
make
```

## The Answer to the documents:


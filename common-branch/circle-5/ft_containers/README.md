# ft_containers

_In this project you will implement the various containers types of the C++ standard
template library._

## Mandatory part

### List :heavy_check_mark:

- **[Reference](http://www.cplusplus.com/reference/list/list/)**
- [The STL list<T> Class Template](https://cs.calvin.edu/activities/books/c++/intro/3e/WebItems/Ch14-Web/STL-List-14.4.pdf)

### Vector :heavy_check_mark:

- **[Reference](http://www.cplusplus.com/reference/vector/vector/)**
- [Size and Capacity of STL Containers](https://www.fluentcpp.com/2017/10/13/size-capacity-stl-containers/)
- [Allocator reference](http://www.cplusplus.com/reference/memory/allocator/)

### Map :heavy_check_mark:

- **[Reference](http://www.cplusplus.com/reference/map/map/)**
- [What is the internal implementation of stl::map in C++](https://stackoverflow.com/questions/17812522/internal-implementation-of-stlmap-in-c)
- [Red Black Tree Wikipedia](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)
- [Trees](https://www.programiz.com/dsa/trees)
- [Red Black Tree](https://www.programiz.com/dsa/red-black-tree)

### Stack :heavy_check_mark:

- **[Reference](http://www.cplusplus.com/reference/stack/stack/)**

### Queue :heavy_check_mark:

- **[Reference](http://www.cplusplus.com/reference/queue/queue/)**

## Bonus part

### Multimap :heavy_check_mark:

- **[Reference](http://www.cplusplus.com/reference/map/multimap/)**
- There are some changes to make to map in order to get the multimap, first you need to allow multiple keys , to make sure that you modify insert prototype to not return a pair of <iterator, bool> but only an iterator and to remove operator[].

### Set :heavy_check_mark:

- **[Reference](http://www.cplusplus.com/reference/set/set/)**
- Set is just like map but instead of storing key value pairs in your tree you only store value. As for multimap, make sure to remove operator[].

### Multiset :heavy_check_mark:

- **[Reference](http://www.cplusplus.com/reference/set/multiset/)**
- As for multimap, there are some changes that you need to make to set in order to get multiset. First you need to allow duplicates value (just as for multimap) and to make sure you modify insert prototype to not return a pair of <iterator, bool> but only an iterator.

### Deque :x:

- **[Reference](http://www.cplusplus.com/reference/deque/deque/)**

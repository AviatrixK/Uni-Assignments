# Weather Data Storage System - Report

## a. Description of the Weather Record ADT

The Weather Record ADT is used to store the basic weather information for a city on a particular date.  
It contains the following fields:
- **Date**: to record the day when temperature is taken.  
- **City**: name of the city.  
- **Temperature**: the temperature value for that city and date.  

In this project, the data is stored using a simple structure (struct) in C++ called `WeatherRecord`.  
It helps in keeping all the related data in one place and makes it easier to insert, retrieve or display weather details.

---

## b. Strategy for Memory Representation (Row-Major vs Column-Major)

The temperature data is stored inside a **2D array**, where:
- Each **row** represents a **year**.
- Each **column** represents a **city**.

There are two ways to access the data from this 2D array:

### Row-Major Order:
- Data is accessed **row by row** (year by year).
- It goes through all the cities for one year first.
- This is faster in C++ because arrays are stored row-wise in memory.
- Example: Access Delhi, Mumbai, Chennai for 2022 → then move to 2023, and so on.

### Column-Major Order:
- Data is accessed **column by column** (city by city).
- It goes through all years for one city first.
- Example: Access all years for Delhi → then all years for Mumbai → then Chennai.

Both methods show the same data, but row-major is usually more memory-efficient in C++.

---

## c. Approach to Handling Sparse Data

Sometimes there may be missing weather records for some city or year.  
To handle this, I used a **sentinel value (-1)** in the array.

If a cell has the value `-1`, it means that no data was recorded for that location and date.  
This is a simple and beginner-friendly way to handle **sparse data** without using complex data structures like linked lists or hash maps.

The program also displays the 2D array clearly so that `-1` values can be seen where data is missing.

---

## d. Time and Space Complexity Analysis

### **Time Complexity**
| Operation | Description | Time Complexity |
|------------|--------------|------------------|
| Insert | Adding a new temperature record | O(1) |
| Delete | Removing a record or replacing it | O(1) |
| Retrieve | Getting a temperature for a city and year | O(1) |

These are all constant-time operations because we use a fixed-size 2D array, and direct indexing is possible.

### **Space Complexity**
| Type | Description | Space Complexity |
|-------|--------------|------------------|
| Storage | 2D array of size (Years × Cities) | O(n × m) |

Here, **n** = number of years and **m** = number of cities.  
Each cell stores one temperature value (double type).

---

## Summary

The Weather Data Storage System successfully:
- Stores and retrieves temperature data using a 2D array.
- Demonstrates row-major and column-major access.
- Handles missing data using a simple sentinel value.
- Analyzes the time and space complexity of operations.

This project helped me understand how data can be arranged in memory and accessed efficiently in C++.

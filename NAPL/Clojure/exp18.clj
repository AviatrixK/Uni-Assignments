;; First collection
(def nums [1 2 3 4 5 6])

(println "Original List:" nums)

(println "Square:" (map (fn [x] (* x x)) nums))

(println "Even Numbers:" (filter even? nums))

(println "Sum:" (reduce + nums))

(println "Take First 3:" (take 3 nums))

(println "Drop First 3:" (drop 3 nums))


;; Using threading macro
(println "Threading Result:"
         (->> nums
              (filter even?)
              (map (fn [x] (* x x)))))


;; Second collection
(def nums2 [10 15 20 25 30])

(println "\nOriginal List 2:" nums2)

(println "Square 2:" (map (fn [x] (* x x)) nums2))

(println "Even Numbers 2:" (filter even? nums2))

(println "Sum 2:" (reduce + nums2))

(println "Take First 2:" (take 2 nums2))

(println "Drop First 2:" (drop 2 nums2))


;; Using threading macro
(println "Threading Result 2:"
         (->> nums2
              (filter even?)
              (map (fn [x] (* x x)))))
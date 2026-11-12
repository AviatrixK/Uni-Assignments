;; List
(def my-list '(10 20 30))

(println "Original List:" my-list)

(def new-list (conj my-list 5))
(println "After conj:" new-list)
(println "First Element:" (first my-list))
(println "Rest of List:" (rest my-list))

;; Vector
(def my-vector [10 20 30])
(println "\nOriginal Vector:" my-vector)

(def new-vector (conj my-vector 40))
(println "After conj:" new-vector)
(println "Element at index 1:" (get my-vector 1))
(println "Count:" (count my-vector))

;; Map
(def my-map {:Go 80 :Java 90})
(println "\nOriginal Map:" my-map)
(def new-map (assoc my-map :Python 85))
(println "After assoc:" new-map)

(def updated-map (dissoc new-map :Go))
(println "After dissoc:" updated-map)
(println "Get Java marks:" (get my-map :Java))


;; Set
(def my-set #{10 20 30})
(println "\nOriginal Set:" my-set)

(def new-set (conj my-set 40))
(println "After conj:" new-set)

(def updated-set (disj new-set 20))
(println "After disj:" updated-set)
(println "Contains 10:" (contains? my-set 10))
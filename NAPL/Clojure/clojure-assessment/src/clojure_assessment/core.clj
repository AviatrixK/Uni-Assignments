(ns clojure-assessment.core
  (:gen-class)
  (:require [ring.adapter.jetty :as jetty]))


(def students
  [{:name "Anna" :marks 85}
   {:name "James" :marks 45}
   {:name "Harry" :marks 90}
   {:name "Ron" :marks 65}
   {:name "Parvati" :marks 95}])

(defn get-names []
  (map :name students))

(defn get-passed-students []
  (filter #(>= (:marks %) 40) students))

(defn get-total-marks []
  (reduce + (map :marks students)))

(defn get-average-marks []
  (/ (get-total-marks) (count students)))

(defn app [request]
  (case (:uri request)

    "/students"
    {:status 200 :body (pr-str (get-names))}

    "/passed"
    {:status 200 :body (pr-str (get-passed-students))}

    "/total"
    {:status 200 :body (str (get-total-marks))}

    "/average"
    {:status 200 :body (str (get-average-marks))}

    {:status 404 :body "Page not found"}))

(defn -main []
  (println "Server started at port 3000")

  (ring.adapter.jetty/run-jetty app
                                {:port 3000}))

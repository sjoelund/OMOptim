# Lesson 7

######################################################################################
### 0) Define files
######################################################################################

set(files hybridAlgo)
  
######################################################################################
### 1) Create the lesson 
######################################################################################
  
add_lesson(mo Lesson7 "${files}")

######################################################################################
### 2) Include dependencies
######################################################################################

include_directories(${EO_SRC_DIR}/src
					${MO_SRC_DIR}/src
					${PROBLEMS_SRC_DIR})
					

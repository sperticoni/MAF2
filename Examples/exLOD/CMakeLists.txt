PROJECT (exLOD)

SET(PROJECT_SRCS 
  main.cpp
  mafLODActor.h
  mafLODActor.cpp
)

IF (WIN32)
  ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SRCS} )
ELSE (WIN32)
  ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SRCS} )
ENDIF (WIN32)

SET(PROJECT_LIBS
  mafVME mafOperations
)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PROJECT_LIBS})

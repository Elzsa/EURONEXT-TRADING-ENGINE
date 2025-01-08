# CMakeLists.txt pour les tests
add_executable(test_matching_engine test_main.cpp)

# Lier les tests avec l'exécutable MatchingEngine
target_link_libraries(test_matching_engine MatchingEngine)

# Ajout des tests
add_test(NAME TestMatchingEngine COMMAND test_matching_engine)

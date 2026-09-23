cmake_minimum_required(VERSION 3.10)
project(MeshViewer3D)

# Spécifier la norme C++ (le standard C++17 est un bon compromis moderne)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver les bibliothèques installées sur le système
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Définir l'exécutable (assure-toi d'avoir un fichier main.cpp)
# Le code source est maintenant dans le dossier src/
add_executable(${PROJECT_NAME} src/main.cpp)

# Indiquer au compilateur où trouver tes futurs fichiers .h / .hpp
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    GLEW::GLEW
)
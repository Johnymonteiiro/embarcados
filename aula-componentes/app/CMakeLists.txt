cmake_minimum_required(VERSION 3.16)

# 1) Use aspas e barras normais (/) ao invés de backslashes (\)
#    aponte para a pasta que CONTÉM o sub-diretório 'digital'
set(EXTRA_COMPONENT_DIRS "C:/Users/Johny/Desktop/SISTEMAS_EMBARCADOS/aula-componentes/component")

# 2) Inclua o projeto IDF
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# 3) Dê um nome ao seu app
project(app)

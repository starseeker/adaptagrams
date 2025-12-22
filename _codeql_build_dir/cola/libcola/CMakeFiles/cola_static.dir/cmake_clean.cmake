file(REMOVE_RECURSE
  "../../libcola.a"
  "../../libcola.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/cola_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

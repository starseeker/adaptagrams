file(REMOVE_RECURSE
  "../../libdialect.a"
  "../../libdialect.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/dialect_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

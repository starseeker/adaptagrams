file(REMOVE_RECURSE
  "../../libproject.a"
  "../../libproject.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/project_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

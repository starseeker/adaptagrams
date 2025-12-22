file(REMOVE_RECURSE
  "../../libavoid.a"
  "../../libavoid.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/avoid_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

file(REMOVE_RECURSE
  "../../libtopology.a"
  "../../libtopology.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/topology_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

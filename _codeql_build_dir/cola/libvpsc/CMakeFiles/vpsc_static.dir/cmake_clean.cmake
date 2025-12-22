file(REMOVE_RECURSE
  "../../libvpsc.a"
  "../../libvpsc.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/vpsc_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

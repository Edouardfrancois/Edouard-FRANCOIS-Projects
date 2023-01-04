# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/criterion-src"
  "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/criterion-build"
  "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/criterion-subbuild/criterion-populate-prefix"
  "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/criterion-subbuild/criterion-populate-prefix/tmp"
  "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/criterion-subbuild/criterion-populate-prefix/src/criterion-populate-stamp"
  "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/criterion-subbuild/criterion-populate-prefix/src"
  "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/criterion-subbuild/criterion-populate-prefix/src/criterion-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/criterion-subbuild/criterion-populate-prefix/src/criterion-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/criterion-subbuild/criterion-populate-prefix/src/criterion-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

# Created by vfx at October 10/31/24 (18:33:23)

# author        : Seongcheol Jeon
# project       : FTH_AR
# file path     : cmake/modules/handleBoostNamespace.cmake
# created date  : 2024.10.31
# modified date : 2024.10.31
# description   :

function(set_boost_namespace target)
    if (DEFINED BOOST_NAMESPACE)
        target_compile_definitions(${target}
                PRIVATE
                BOOST_NAMESPACE=${BOOST_NAMESPACE}
        )
    endif ()
endfunction()
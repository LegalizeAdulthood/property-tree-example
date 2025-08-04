find_path(TCB_SPAN_INCLUDE_DIR "tcb/span.hpp")

if(TCB_SPAN_INCLUDE_DIR)
    add_library(tcb_span INTERFACE)
    target_include_directories(tcb_span INTERFACE TCB_SPAN_INCLUDE_DIR)
    add_library(Tcb::Span ALIAS tcb_span)
endif()

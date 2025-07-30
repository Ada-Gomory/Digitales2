.global reset_vector
.extern _start
.code 32

.section .reset_vector_code
reset_vector: 
  B _start
.end

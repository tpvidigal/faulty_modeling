set N 10000

cd ../../
catch { exec make } msg

for {set i 0} {$i < $N} {incr i} {
	catch { exec ./sc_module.x } msg
}

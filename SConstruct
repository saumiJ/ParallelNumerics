import os, sys

vars = Variables(None, ARGUMENTS)

env = Environment(variables = vars, ENV = os.environ)
Help(vars.GenerateHelpText(env))

conf = Configure(env)

env.Append(CCFLAGS = ["-g3", "-O0", "-Wall", "-std=c++11"])

env["CXX"] = 'mpic++'
env = conf.Finish()

env.Program('main', [	'test/test.hpp', 
			'test/test_all.cpp', 
			'test/test_vSum.cpp', 
			'test/test_vDot.cpp',
			'test/test_vNorm.cpp',
			'vSum/vSum.hpp', 
			'vSum/vSumF.cpp', 
			'vSum/vSumS.cpp', 
			'vDot/vDot.hpp',
			'vDot/vDotF.cpp',
			'vDot/vDotS.cpp',
			'vNorm/vNorm.hpp',
			'vNorm/vNormF.cpp',
			'vNorm/vNormS.cpp',
			'main.cpp'])

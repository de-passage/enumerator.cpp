require "rakeIDE"
require "rakeIDE/g++"

IDE.compiler = Tools::Compiler::GXX
IDE.linker = Tools::Linker::GXX

IDE.compiler.options = [ "--std=c++1y", "-Wall", "-Wall", "-Wextra" ]

IDE.default_target = :release
IDE.available_targets = [:release, :debug]

rule(/^example_.+/) do |t|
	source = t.name.match(/^example_(.+)/)[1]
	source = File.join("example", source)
	Rake::Task[:target].invoke 'release'
	Rake::Task[:source].invoke source
end


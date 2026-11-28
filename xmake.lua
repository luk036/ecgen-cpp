set_languages("c++20")

add_rules("mode.debug", "mode.release", "mode.coverage")
add_requires("doctest", "fmt", "nanobench", "spdlog")

add_includedirs("include", "../py2cpp/include")

if is_mode("coverage") then
    add_cxflags("-ftest-coverage", "-fprofile-arcs", {force = true})
end

if is_plat("linux") then
    set_warnings("all", "error")
    -- Termux/Android ships its libc++ headers under $PREFIX
    local prefix = os.getenv("PREFIX")
    if prefix then
        add_cxflags("-Wno-unused-command-line-argument", {force = true})
        add_sysincludedirs(prefix .. "/include/c++/v1", prefix .. "/include", {public = true})
    end
    -- host-native tuning for auto-vectorization
    if is_mode("release") then
        add_cxflags("-march=native", "-mtune=native", {force = true})
    end
elseif is_plat("windows") then
    add_cxflags("/EHsc /utf-8 /W4 /WX /wd4702", {force = true})
    if is_mode("release") then
        add_cxflags("/arch:AVX2", {force = true})
    end
end

target("Ecgen")
    set_kind("static")
    add_files("source/*.cpp")
    add_packages("fmt", "spdlog")

target("test_ecgen")
    add_deps("Ecgen")
    add_files("test/source/*.cpp")
    add_packages("doctest", "fmt", "spdlog")
    add_tests("default")

target("test_emk")
    add_deps("Ecgen")
    add_files("bench/BM_EMK.cpp")
    add_packages("nanobench")

target("test_set_partition")
    add_deps("Ecgen")
    add_files("bench/BM_set_partition.cpp")
    add_packages("nanobench")

target("bench_compare")
    add_deps("Ecgen")
    add_files("bench/compare.cpp")
    add_packages("fmt", "spdlog")

target("verify_output")
    add_deps("Ecgen")
    add_files("bench/verify_output.cpp")
    add_packages("fmt", "spdlog")

target("verify_old_new")
    add_deps("Ecgen")
    add_files("bench/verify_old_new.cpp")
    add_packages("fmt", "spdlog")

target("spdlog_example")
    add_deps("Ecgen")
    add_files("examples/spdlog_example.cpp")
    add_packages("fmt", "spdlog")

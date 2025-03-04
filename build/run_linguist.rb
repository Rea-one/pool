# run_linguist.rb

require 'linguist'

# 定义语言检测函数（基于文件路径）
def detect_language_from_file(file_path)
  # 检查文件是否存在
  unless File.exist?(file_path)
    return "File not found: #{file_path}"
  end

  # 创建 Linguist::FileBlob 对象
  blob = Linguist::FileBlob.new(file_path)

  # 获取语言名称
  if blob.language
    blob.language.name
  else
    "Unknown"
  end
end

# 从参数中读取文件路径
if ARGV.empty?
  puts "Usage: ruby run_linguist.rb <file_path>"
  exit(1)
end

file_path = ARGV[0]
language = detect_language_from_file(file_path)

# 输出语言名称（供 C++ 程序捕获）
puts language
s = input()

# カンマで分割して空白を除去
items = [x.strip() for x in s.split(",")]

# シングルクオート付きで出力（set形式）
result = "{" + ", ".join(f"'{x}'" for x in items) + "}"

print(result)
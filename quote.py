s = input()

if "," in s:
    items = [x.strip() for x in s.split(",")]
elif "、" in s:
    items = [x.strip() for x in s.split("、")]

# 要素に1つでも2文字以上があれば全部ダブルクオート
quote = '"' if any(len(x) >= 2 for x in items) else "'"

result = "{" + ", ".join(f"{quote}{x}{quote}" for x in items) + "}"

print(result)
import os
import re

dir_path = r"C:\Users\isaac\source\repos\alienAttack\AlienAttack26"
files = ["AlienArmy.cpp", "gameFunctions.cpp", "LifeIconContainer.cpp", "MissileContainer.cpp", "Pixie.cpp", "Ship.cpp"]

bad_comment_pattern = re.compile(
    r"(//[^\n]*\n)?\s*/\*\s*\* Name: main\s*\* Arg\(s\): \(\)\s*\* Returns: int\s*\*\s*\* Main function\s*\*/\s*(//[^\n]*\n)?\s*(.*?\([^)]*\)[^{;]*{?)",
    re.MULTILINE | re.DOTALL
)

def fix_comments():
    for filename in files:
        filepath = os.path.join(dir_path, filename)
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()

        def replacer(match):
            comment_before = match.group(1)
            comment_after = match.group(2)
            sig = match.group(3).strip()

            single_line_comment = ""
            if comment_before and comment_before.strip().startswith("//"):
                single_line_comment = comment_before.strip()[2:].strip()
            elif comment_after and comment_after.strip().startswith("//"):
                single_line_comment = comment_after.strip()[2:].strip()

            # Parse signature
            # Remove any trailing { or whitespace
            sig_clean = re.sub(r'\s*\{?$', '', sig).strip()
            
            # Extract arguments
            arg_match = re.search(r'\(([^)]*)\)', sig_clean)
            args = arg_match.group(1).strip() if arg_match else ""

            # Extract name and return type
            name_and_type = sig_clean[:arg_match.start()].strip()
            
            # Find the last word which is the function name
            parts = name_and_type.split()
            
            # Handle Constructors/Destructors where there is no return type
            # They usually have the class name like Class::Class or Class::~Class
            name_part = parts[-1]
            if "::" in name_part:
                class_name, func_name = name_part.split("::", 1)
                if class_name == func_name or func_name == "~" + class_name:
                    ret_type = ""
                    func_name_full = name_part
                else:
                    ret_type = " ".join(parts[:-1]).strip()
                    func_name_full = name_part
            else:
                if len(parts) == 1: # standalone function, likely no return type specified but usually shouldn't happen, except main
                    ret_type = ""
                    func_name_full = name_part
                else:
                    ret_type = " ".join(parts[:-1]).strip()
                    func_name_full = name_part

            # Format the new comment block
            ret_str = ret_type if ret_type else "void" # Or empty? The prompt says `Returns: void` for draw. Let's use ret_type or none.
            if not ret_type: # For constructors/destructors
                ret_str = "N/A" # or omit? Let's use N/A

            new_block = f"/*\n * Name: {func_name_full}\n * Arg(s): {args if args else '()'}\n * Returns: {ret_str}\n *\n * {single_line_comment}\n */\n{sig}"
            return new_block

        new_content, count = bad_comment_pattern.subn(replacer, content)
        if count > 0:
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(new_content)
            print(f"Replaced {count} instances in {filename}")

if __name__ == "__main__":
    fix_comments()
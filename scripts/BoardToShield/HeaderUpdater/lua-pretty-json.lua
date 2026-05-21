--[[
MIT License

Copyright (c) 2022 - 2025 Jonas Strittmatter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

--]]

--[[ json_pretty_print.lua

Utility function that turns a Lua table into a nicely formatted JSON string (pretty-printing).

Note:
- uses the Neovim-specific function vim.tbl_count, so replace that if that function
is not available to you!
- each item is indented by 2 spaces

---

Function signature:
pretty_print(data: table, compare: function, escape_special_chars: boolean) -> string

Basic usage:

json_pretty_print:pretty_print({
  key = {
    a_table = {
      A = "v1",
      B = "v2",
    },
    an_array = { "one", 2 },
  },
})

returns the string:

{
  "key": {
    "a_table": {
      "A": "v1",
      "B": "v2"
    },
    "an_array": [
      "one",
      2
    ]
  }
}

By default, keys in tables are sorted alhabetically. To change this, pass a different
comparison function to stringify. This function should take as arguments the two keys
to compare and return a boolean that determines whether the first argument should be
output before the second or not.

If you want to escape any special characters, set escape_special_chars to true.
Otherwise each table value will be output as is.

For more examples, check out the tests in json_pretty_print_spec.lua.
--]]

local M = {}

function M:escape_chars(str)
  -- Escape backslashes (I couldn't get this to work with gsub / regexes)
  local chars = {}
  for i = 1, #str do
    local cur_char = str:sub(i, i)
    if cur_char == "\\" then
      chars[#chars + 1] = "\\"
    end
    chars[#chars + 1] = cur_char
  end

  local item = table.concat(chars)
  -- Escape escape sequences (see http://www.lua.org/manual/5.1/manual.html#2.1)
  return item:gsub("[\a\b\f\n\r\t\v\\\"']", {
    ["\a"] = "\\a",
    ["\b"] = "\\b",
    ["\f"] = "\\f",
    ["\n"] = "\\n",
    ["\r"] = "\\r",
    ["\t"] = "\\t",
    ["\v"] = "\\v",
    ['"'] = '\\"',
    ["'"] = "\\'",
  })
end

function M:format_string(value)
  local result = self.escape_special_chars and self:escape_chars(value) or value
  self:emit(([["%s"]]):format(result), true)
end

local pairs_by_keys = function(tbl, compare)
  local keys = {}
  for key, _ in pairs(tbl) do
    table.insert(keys, key)
  end
  table.sort(keys, compare)
  local i = 0
  -- Return an iterator function
  return function()
    i = i + 1
    return keys[i] and keys[i], tbl[keys[i]] or nil
  end
end

local table_count = function(table)
  local count = 0
  for _ in pairs(table) do
     count = count + 1
  end
  return count
end

function M:format_table(value, add_indent)
  local count = table_count(value)
  self:emit("{\n", add_indent)
  self.indent = self.indent + 2
  local prev_indent = self.indent
  local i = 1
  for k, v in pairs_by_keys(value, self.compare) do
    self:emit(('"%s": '):format(k), true)
    if type(v) == "string" then
      -- Reset indent temporarily
      self.indent = 0
    end
    self:format_value(v)
    self.indent = prev_indent
    if i == count then
      self:emit("\n")
    else
      self:emit(",\n")
    end
    i = i + 1
  end
  self.indent = self.indent - 2
  self:emit("}", true)
end

function M:format_array(value)
  local array_count = #value
  self:emit("[\n")
  self.indent = self.indent + 2
  for i, item in ipairs(value) do
    -- Also indent the following items
    self:format_value(item, true)
    if i == array_count then
      self:emit("\n")
    else
      self:emit(",\n")
    end
  end
  self.indent = self.indent - 2
  self:emit("]", true)
end

function M:emit(value, add_indent)
  if add_indent then
    self.out[#self.out + 1] = (" "):rep(self.indent)
  end
  self.out[#self.out + 1] = value
end

function M:format_value(value, add_indent)
  if value == nil then
    self:emit("null")
  end
  local _type = type(value)
  if _type == "string" then
    self:format_string(value)
  elseif _type == "number" then
    self:emit(tostring(value), add_indent)
  elseif _type == "table" then
    local count = table_count(value)
    if count == 0 then
      self:emit("{}")
    elseif #value > 0 then
      self:format_array(value)
    else
      self:format_table(value, add_indent)
    end
  end
end

local default_compare = function(a, b)
  return a:lower() < b:lower()
end

function M:pretty_print(data, compare, escape_special_chars)
  self.compare = compare or default_compare
  self.escape_special_chars = escape_special_chars
  self.indent = 0
  self.out = {}
  self:format_value(data)
  return table.concat(self.out)
end

return M
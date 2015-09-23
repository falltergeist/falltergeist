--
-- Global definitions
--

-- load OOP facilities
class = require("vendor.middleclass")

--- A trick for C++ object wrapper classes
-- @param tClass class table, created by "middleclass" library
-- @param eClass engine class table, created by Luabridge
--
function class.Object.wrapEngineClass(tClass, eClass)
    assert(type(tClass) == "table", "Make sure you are using 'Class:wrapEngineClass' (with colon).")
    assert(type(tClass.__instanceDict) == "table", "wrapEngineClass should only be called on a class table.")

    -- cache names of engine class members that can be "get", "set" or called
    tClass.__membersGet = {}
    tClass.__membersSet = {}
    tClass.__membersCall = {}
    local function getMembers(classDef, level)
        level = level or 0
        for k, _ in pairs(classDef) do
            if type(k) == "string" and string.sub(k, 1, 2) ~= "__" then -- instance method
                -- create a wrapping closure for C++ class instance method
                tClass.__membersCall[k] = function(self, ...)
                    return self.obj[k](self.obj, ...)
                end
            end
        end
        for k, _ in pairs(classDef.__propget) do
            tClass.__membersGet[k] = true
        end
        for k, _ in pairs(classDef.__propset) do
            tClass.__membersSet[k] = true
        end
        if type(rawget(classDef, "__parent")) == "table" then
            getMembers(classDef.__parent, level + 1)
        end
    end
--    print(tostringRecursive(eClass.__class))
    getMembers(eClass.__class)

    -- this is a metatable of class instances
    local mt = tClass.__instanceDict

    -- allows to get property values and call methods of C++ object
    function mt:__index(k)
        if (tClass.__membersCall[k] ~= nil) then
            return tClass.__membersCall[k]
        elseif (tClass.__membersGet[k] ~= nil) then
            return self.obj[k]   -- self is the instance
        end
        return mt[k]
    end
    -- allows to set property values of C++ object
    function mt:__newindex(k, v)
        if (tClass.__membersSet[k] ~= nil) then
            self.obj[k] = v
        else
            rawset(self, k, v)
        end
    end
end


-- aliases for some game object constructors
Point = game.Point
Size = game.Size



--- Converts given value to string recursively
-- @param val value to print
-- @param indent don't use
-- @param mem don't use
--
function tostringRecursive(val, indent, mem)
    local s = tostring(val)
    if (type(val) == "table" or type(val) == "userdata") then
        mem = mem or {}
        if (mem[val] ~= nil) then
            return s .. " (recursion)"
        end
        mem[val] = true
    end
    if (type(val) == "table") then
        indent = (indent or "") .. "    "
        for k, v in pairs(val) do
            s = s .. " \n" .. indent .. tostring(k) .. " = " .. tostringRecursive(v, indent, mem)
        end
    end
    return s
end


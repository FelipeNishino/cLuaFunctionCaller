function factorial(x)
    if x == 0 or x == 1 then
        return x
    else
        return x * factorial(x-1)
    end
end

function power(x, y)
    return x^y
end

function nothing(x)
    return x
end

function bhaskara(a, b, c)
    delta = (b^2) - 4*a*c

    if delta < 0 then
        return "Não tem raíz"
    else
        x1 = (-b + math.sqrt(delta)) / (2 * a)
        if delta > 0 then
            x2 = (-b - math.sqrt(delta)) / (2 * a)
            return "Raízes: " .. x1 .. "; " .. x2
        else
            return "Raíz: " .. x1
        end
    end
end

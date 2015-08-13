-- state is C++ object
init = function(state)
    state.modal = true
    state.fullscreen = true

    background = game.ui.Image("art/intrface/mainmenu.frm")
    print(background)

    state:addImage(background)

end

-- state is C++ object
think = function(state)
end

-- state is C++ object
-- event is C++ object
handle = function(state, event)
    print(event.name)
end

-- state is C++ object
render = function(state)
end

# Alexa Szlykowicz
# Text Based Game
# Must visit all the planets and collect the artifacts
# before heading to the Boss in Dark Morrows
# User Controls: go South, go North, go East, go West
#                get Artifact 1, get Artifact 2, Artifact 3, Artifact 4, Artifact 5, Artifact 6
#                show inventory function
# print error when trying to acquire item in HeliQ
print('Planetary Text Base Game\n')
planets = {
        'HeliQ Space Station': {'North': 'Sandara', 'South': 'Helios', 'East': 'Lotacus', 'West': 'Iris'},
        'Sandara': {'South': 'HeliQ Space Station', 'East': 'Petrius',},
        'Helios': {'North': 'HeliQ Space Station', 'East': 'Fateim'},
        'Fateim': {'West': 'Helios'},
        'Iris': {'East': 'HeliQ Space Station'},
        'Petrius': {'West': 'Sandara'},
        'Lotacus': {'North': 'Dark Morrows'},
}

items = {'Sandara': 'Artifact 1', 'Helios': 'Artifact 2', 'Fateim': 'Artifact 3', 'Iris': 'Artifact 4', 'Petrius':
         'Artifact 5', 'Lotacus': 'Artifact 6'}
# start the player on airship
currentPlanet = 'HeliQ Space Station'
inventory = []


def print_instructions():

    print('Collect all six artifacts before entering Dark Morrows to defeat Naruko. If you do not have all the '
          'artifacts, you will be defeated.')
    print('Move commands: go South, go North, go East, go West')
    print('Add to Inventory: get Artifact [number]')
    print('\n')


print_instructions()

while True:
    print('You are on', currentPlanet)
    print('Inventory :', inventory)

    print('------------------')
    print('Enter your move:')

    user_input = input().split(" ", 1)
    planet = user_input[1]
    print('\n')

    if user_input[0].lower() == 'go':
        if planet not in planets[currentPlanet]:
            print('Error')
            break
        else:
            if planets[currentPlanet][planet.capitalize()] == 'Dark Morrows':
                if len(inventory) == 6:
                    print('You have defeated Naruko!')
                    break
                else:
                    print('You are defeated!')
                    break
            currentPlanet = planets[currentPlanet][planet]
    print('You see ', items[currentPlanet])
    if user_input[0].lower() == 'get':
        if planet not in items.values():
            print('Error')
            break
        elif planet == items[currentPlanet]:
            if planet in inventory:
                print('item is already in inventory')
            else:
                inventory.append(planet)
                print('You collected', planet)

        else:
            print('Cannot get item')


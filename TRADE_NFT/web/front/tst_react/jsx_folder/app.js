let n = 0

function render() {
    
    const title = React.createElement('h1', {},
    'Bonjour tous le monde',
    React.createElement('span', {}, n)
    )
    ReactDOM.render(title, document.querySelector('#app'))
}

render()

window.setInterval(() => {
    n++
    render()
}, 50)


/* 
jANVIER AVRIL 2 JOUR SEMAINE

R ET D = CHERCHER LES MEILLEURS DIRECTION DU PROJET 
COM AU SEINS DE EPITECH EPITA 42


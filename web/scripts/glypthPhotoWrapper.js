const photoWrappers = document.querySelectorAll('.photo-wrapper')

photoWrappers.forEach((item, i) => {
  const photo = item.querySelector('.photo')

  const photoShadow = photo.cloneNode(true);
  photoShadow.style.filter = 'brightness(1.5) saturate(1) blur(48px)'
  photoShadow.style.zIndex = 'auto'
  item.appendChild(photoShadow)
})

const content = document.querySelector('.content')
const modal = document.querySelector('.modal')
const toggle = document.querySelector('.toggle')
let isActive = false

toggle.onclick = function(){
  if (isActive) {
    content.classList.remove('active')
    modal.classList.remove('active')
    isActive = false
  } else {
    content.classList.add('active')
    modal.classList.add('active')
    isActive = true
  }
}

const mainContent = document.querySelector('.main-content')
const songModal = document.querySelector('.song-modal')
const songOpen = document.querySelector('#songOpen')
const songClose = document.querySelector('#songClose')
let isSongActive = false

function windowPos() {
  songModal.style.top = `${songOpen.getBoundingClientRect().top - content.offsetTop - 2}px`
}

songOpen.onclick = function(){
  var distanceY = window.innerHeight - songOpen.getBoundingClientRect().bottom + content.offsetTop - 390
  songModal.style.transform = `translateY(${distanceY}px)`
  content.classList.add('active')
  songModal.classList.add('active')
  modal.style.display = 'none'
  isSongActive = true
}

songClose.onclick = function(){
  songModal.style.transform = `translateY(0px)`
  content.classList.remove('active')
  songModal.classList.remove('active')
  modal.style.display = 'block'
  isSongActive = false
}

windowPos()
window.addEventListener('resize', windowPos);
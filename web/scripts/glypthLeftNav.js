const menuItems = document.querySelectorAll('nav ul li');
    menuItems.forEach(item => {
      item.addEventListener('click', () => {
        menuItems.forEach(li => li.classList.remove('active'));
        item.classList.add('active');
      });
    });

    // Dropdown change simulation
    const versionSelector = document.getElementById('versionSelector');
    versionSelector.addEventListener('change', () => {
      alert(`Switched to ${versionSelector.value} documentation.`);
    });
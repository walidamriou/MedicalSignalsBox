/*
Medical Signals Box project
Developed by Walid Amriou
2019 
*/

const noble = require('noble-uwp') //use noble-uwp in windows not noble like Linux

noble.on('stateChange', state => {
  console.log('state change', state)
  if (state === 'poweredOn') {
    noble.startScanning()
  } else {
    noble.stopScanning()
  }
})

noble.on('discover', peri => {
  noble.stopScanning()
  const ad = peri.advertisement
  console.log("ad name: ", ad.localName)
  if ("null" == "null") { //the origin is ad.localName == "MedicalSignalsBox" but not work in windows
    console.log("found target esp")
    peri.connect(error => {
      console.log("conected")
      if (error) {
        console.log("connection error:", error)
      }
      peri.discoverServices([], (error, services) => {
        if (error) {
          console.log("discover service error", error)
        }
        services.forEach(service => {
          console.log("service uuid: ", service.uuid)
          if (service.uuid == "4fafc2011fb5459e8fccc5c9c331914b") {
            console.log("ff")
            service.discoverCharacteristics([], (error, charas) => {
              if (error) {
                console.log("discover characteristics error", error)
              }
              charas.forEach(chara => {
                console.log("found chara: ", chara.uuid)
                if (chara.uuid == "beb5483e36e14688b7f5ea07361b26a8") {
                   chara.read(function (error, data) {});
                      chara.on('read', function (data, isNotification) {
                        console.log('the data received: ' + data.toString('utf8')); //because the data is a buffer
                  }.bind(this));

                }
              })
            })
          }
        })
      })
    })
  }
})

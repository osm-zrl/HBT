import React, { useState } from 'react';
import { Text, Image,Vibration, SafeAreaView, TouchableOpacity, View, StyleSheet } from 'react-native';




function App() {
  const [progressBarDisplay, setPBD] = useState("none");
  const [errorMessageDisplay, setEMD] = useState("none");
  const [buttonDisabled, setButtonDisabled] = useState(false);
  const [progressBarWidth, setPBW] = useState(0)




  const handleClick = ()=>{
    setButtonDisabled(true)
    setPBD("block")
    setEMD("none")
    Vibration.vibrate(100)

    fetch("http://192.168.1.100/trigger",{method:"POST"})
    .then(response=>{
      if(response.status==200){

        const animationInterval = setInterval(() => {

          setPBW(prevPBW => {
            const newPBW = prevPBW + 5;
            console.log(`here ${newPBW}`);
            return newPBW;
          });

        }, 1000);

        setTimeout(()=>{
          setButtonDisabled(false)
          setPBD("none")
          setPBW(0)


          clearInterval(animationInterval)

        },21000)


      }else{
        setEMD("block")
        setButtonDisabled(false)
        setPBD("none")
        setPBW(0)
        Vibration.vibrate(500)
      }
    })
    .catch(error=>{
      setButtonDisabled(false)
      setPBD("none")
      setPBW(0)
      setEMD("block")
      Vibration.vibrate(500)
    })


  }

  return (
    <SafeAreaView style={styles.container}>
      <TouchableOpacity disabled={buttonDisabled} style={styles.button} onPress={handleClick}>
        <Image style={styles.bell} source={require('./assets/bell.png')}></Image>
      </TouchableOpacity>

      <Text style={{...styles.text,display:errorMessageDisplay}}>Failed To Connect To Buzzer</Text>

      <View style={{...styles.progressBar,display:progressBarDisplay}}>
        <View style={{...styles.subProgressBar,width:`${progressBarWidth}%`,}}></View>
      </View>

    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container:{
    flex:1,
    justifyContent:"center",
    alignItems:"center",
    backgroundColor:"#F5F5F5",
    gap:20
  },
  button:{
    backgroundColor:"#48CFCB",
    padding:20,
    borderRadius:20,

  },
  bell:{
    height:90,
    width:75
  },
  progressBar:{
    height:10,
    width:'50%',
    backgroundColor:'#424242',
    marginHorizontal:'auto',
    borderRadius:10,
    overflow:'hidden'
  },
  subProgressBar:{
    backgroundColor:'#48CFCB',
    height:10,

  },
  text:{
    color:"red"
  }
});

export default App;

![d2](https://github.com/user-attachments/assets/d54e49de-5c15-4579-8340-59cda95358d0)# Hermes - Конфигурируемый веб-сервер

![20250423_2050_Логотип Hermes Веб-сервер_simple_compose_01jshw9156epms8ejnt4017tdg](https://github.com/user-attachments/assets/d2a5c573-1755-460e-ab97-c88cf96e9bde)

Hermes — это веб-сервер на C++, поддерживающий HTTP-маршрутизацию, проксирование и обработку статических файлов. Построен с использованием Boost.Beast для HTTP и Boost.Asio для асинхронного ввода-вывода.

!<?xml version="1.0" encoding="utf-8"?><svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" data-d2-version="v0.6.9-HEAD" preserveAspectRatio="xMidYMid meet" viewBox="0 0 1180 1078"><svg class="d2-789827171 d2-svg" width="1180" height="1078" viewBox="-74 -101 1180 1078"><rect x="-74.000000" y="-101.000000" width="1180.000000" height="1078.000000" rx="0.000000" fill="#FFFFFF" class=" fill-N7" stroke-width="0" /><style type="text/css"><![CDATA[
.d2-789827171 .text-bold {
	font-family: "d2-789827171-font-bold";
}
@font-face {
	font-family: d2-789827171-font-bold;
	src: url("data:application/font-woff;base64,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");
}
.d2-789827171 .text-italic {
	font-family: "d2-789827171-font-italic";
}
@font-face {
	font-family: d2-789827171-font-italic;
	src: url("data:application/font-woff;base64,d09GRgABAAAAAArIAAoAAAAAEUgAARhRAAAAAAAAAAAAAAAAAAAAAAAAAABPUy8yAAAA9AAAAGAAAABgW1SVeGNtYXAAAAFUAAAAfwAAAJwCxQKEZ2x5ZgAAAdQAAAS0AAAGVKoeAY5oZWFkAAAGiAAAADYAAAA2G7Ur2mhoZWEAAAbAAAAAJAAAACQLeAi4aG10eAAABuQAAABQAAAAUCRCAwFsb2NhAAAHNAAAACoAAAAqEDgOtG1heHAAAAdgAAAAIAAAACAALAD2bmFtZQAAB4AAAAMmAAAIMgntVzNwb3N0AAAKqAAAACAAAAAg/8YAMgADAeEBkAAFAAACigJY//EASwKKAlgARAFeADIBIwAAAgsFAwMEAwkCBCAAAHcAAAADAAAAAAAAAABBREJPAAEAIP//Au7/BgAAA9gBESAAAZMAAAAAAeYClAAAACAAA3icbMw/zsEAHIDhp1/71b+iSMzuYmFrxAWasInE4hwuIEziAEwGZ3GSn6Szd3yGF4lUgkLmhKlSKjczt1RZq23t7B0jaHyhslLbNH6IiE+84xXPeMQ9bnGNS5yb668Sf1KZf7mWto6unkLfwFBpZGzCFwAA//8BAAD//8V/HTcAeJx8k0tsE9cXxs+9M/EQYkPs8SN2HE/sO55xjB+xrz1jx7Gd4BDnYYcQCP+IxDz0J22hFKVUCCoaUYiEqm7qSmxaIVGpUtWKJd2wgU0XUSt2VUWXVdsgkUqVIi9oVY+rsYNJsuj66n7fOd/vO9ABIgC+jO8CA51wECxgA6C8l2GoqhIHQ2WZcJwq8zwn3kbrtz9nC6d+D3zxV0hgi7e+mf7j7AN8t34JfVi5eVNb/Gh5+X+bm1oQ/bQJAIAg3ajhML4HAkCHT5KSiRymcbuDkyTiO4BtVrudxhXVYTAg3/RbyuCp1VLqWI/CK9LQmcOibyoTKPQTsWIsXJ8p371WVIMD/XL2/PXhTCXZ3xsXwk0PAoAv4Cp06XNTxstThvBehqzNpFAgVV6byWvPcriqbSJbfQWltPXWH6jhKjCtP2RtZg1X6ysAgJt64aaetfkat9usBgMhDE/jSjIhEULWHi1dmbp14kJi9MzyxdLEMq5OnZx9M6a9RMXZo2kKbR0ZV8EE9tc6HE+YXUrfLr17+fh7xy9dUcf+f/r89MRZXB0/vnjZrP2K7NoLND83rkRbWRobNaThexAEcPgkWW1ml0xIsqwHqyjtYA0Gm9XucNibcz8vrATSffPq8LGwvxTMJJcymbMCdY5H/Mm+mFiKJjJvGIeGDh2Kj6XEuD3imlTjc/FEIOIZEAZ7pag97C6qQ4sJQFABwElcBU7fhqhejjBfXX1sQj+YnlzF5UKh/rC1t9yooZdoC6x6Ag5fGzpVKUNUYjDIcUVV2w14OFIKTZ2mctbM8rlz+X0sWbBIR8WQLe4WC0khZlycH39/iQa8Wc014Y+ORKI/S77gZCWez7b9sIzXwaY3eZfffxsOWZhuqVzddpzx73WU+888rqf2WmLwN2roCdoCF/h3+jXpeg3tRjNU0enoPH47eSE8vTSojnqMHdp3nf2FYF/a4ek79lkDM5YBkjxtvHjuyMpcKDIbd9MD+Vm/00xtAvJ39ZjcMWEeEIQaNfgbr4NFd0wmVJ4yOuVtq3dGDTfKqwiZGQOH9tuNebMTv13/lOtkLAhnWLbVHwEAPUNb0NNsI0ebjbFZOYbw+qTEZ+AY4VyeYwfmIrnkvlxpmGUn3BORI2hjUoyNpgRR+x6FrD2m6WBE+/pV9rTJupl9h6qHTXYTZ3Zlj7xeD/YvRHYy//j+zvCf3r8mRdvI62WEdgNv7fEB2oLuHXs4OOnV/F1sXynstPV2u8SSkEUblVC2c2xfPqM9BdT4p1FDq2gL5L03tPeE9AtqHdCXsYpz0DEiBbMDqUg6NBmKTLkjPPVKMaU/lxicMyYCkhCIEJcsuHIDh0b9oidgdYUFj2TxDYfCY3595uFGDS3gS+Deboyi8iSPKUc5wuhe2yAfjSRYlC52lcTR3hvG1TTj9h1wdZm7o8Z8+KDLhCzpjjt3ctoLi8Xj2d+hcgd17VSjhv5EG+B8rf26Hfz2CTzIKiybK2dZdqKvGDpS0g8tcMJ4WDULPFK0H3mnjhUtaK4pQlt9yQCgX9AGmAAoQ3m73UEVXRDdLpZE1sCyZpH/pKzV0Yb2nEwTcVJETs0FAP8CAAD//wEAAP//jpFLagABAAAAARhRyhvkvV8PPPUAAQPoAAAAANhdoMwAAAAA3WYvN/69/t0IHQPJAAIAAwACAAAAAAAAAAEAAAPY/u8AAAhA/r39vAgdA+gAwv/RAAAAAAAAAAAAAAAUAnQAJADIAAACJgA5Am4AIwD8ACMCJgAjAisAIwH6AAwB/gBdAhkAJwIXACcB4QAlAPgALAINAB8CGQAnAVYAHwGS//wBRQA8AhAAOAHAADsAAAAuAC4AYAB6AIgArADUARQBKAFgAZgB0gH0Ah4CWAJ2ArIC4AMMAyoAAAABAAAAFACMAAwAZgAHAAEAAAAAAAAAAAAAAAAABAADeJyclNtOG1cUhj8H2216uqhQRG7QvkylZEyjECXhypSgjIpw6nF6kKpKgz0+iPHMyDOYkifodd+ib5GrPkafoup1tX8vgx1FQSAE/Hv2OvxrrX9tYJP/2KBWvwv83ZwbrrHd/NnwHb5oHhneYL/5meE6Dxv/GG4waLw13ORBo2v4E97V/zT8KU/qvxm+y1b90PDnPK5vGv5yw/Gv4a94wrsFrsEz/jBcY4vC8B02+dXwBvewmLU699gx3OBrtg032QZ6TKhImZAxwjFkwogzZiSURCTMmDAkYYAjpE1Kpa8ZsZBj9MGvMREVM2JFHFPhSIlIiSkZW8S38sp5rYxDnWZ216ZiTMyJPE6JyXDkjMjJSDhVnIqKghe0aFHSF9+CipKAkgkpATkzRrTocMgRPcZMKHEcKpJnFpEzpOKcWPmdWfjO9EnIKI3VGRkD8XTil8g75AhHh0K2q5GP1iI8xPGjvD23XLbfEujXrTBbz7tkEzNXP1N1JdXNuSY41q3P2+YH4YoXuFv1Z53J9T0a6H+lyCecaf4DTSoTkwzntmgTSUGRu49jX+eQSB35iZAer+jwhp7Obbp0aXNMj5CX8u3QxfEdHY45kEcovLg7lGKO+QXH94Sy8bET689iYgm/U5i6S3GcqY4phXrumQeqNVGFN5+w36F8TR2lfPraI2/pNL9MexYzMlUUYjhVL5faKK1/A1PEVLX42V7d+22Y2+4tt/iCXDvs1brg5Ce3YHTdVIP3NHOun4CYATknsuiTM6VFxYV4vybmjBTHgbr3SltS0b708XkupJKEqRiEZIozo9Df2HQTGff+mu6dvSUD+Xump5dV3SaLU6+uZvRG3VveRdblZGUCLZtqvqKmvrhmpv1EO7XKP5Jvqdct5xGh4i52+0OvwA7P2WWPsbL0dTO/vPOvhLfYUwdOSWQ1lKZ9DY8J2CXgKbvs8pyn7/VyycYZH7fGZzV/mwP26bB3bTUL2w77vFyL9vHMf4ntjupxPLo8Pbv1NB/cQLXfaN+u3s2uJuenMbdoV9txTMzUc3FbqzW5+wT/AwAA//8BAAD//3KhUUAAAAADAAD/9QAA/84AMgAAAAAAAAAAAAAAAAAAAAAAAAAA");
}]]></style><style type="text/css"><![CDATA[.shape {
  shape-rendering: geometricPrecision;
  stroke-linejoin: round;
}
.connection {
  stroke-linecap: round;
  stroke-linejoin: round;
}
.blend {
  mix-blend-mode: multiply;
  opacity: 0.5;
}

		.d2-789827171 .fill-N1{fill:#170206;}
		.d2-789827171 .fill-N2{fill:#535152;}
		.d2-789827171 .fill-N3{fill:#787777;}
		.d2-789827171 .fill-N4{fill:#CCCACA;}
		.d2-789827171 .fill-N5{fill:#DFDCDC;}
		.d2-789827171 .fill-N6{fill:#ECEBEB;}
		.d2-789827171 .fill-N7{fill:#FFFFFF;}
		.d2-789827171 .fill-B1{fill:#023324;}
		.d2-789827171 .fill-B2{fill:#048E63;}
		.d2-789827171 .fill-B3{fill:#49BC99;}
		.d2-789827171 .fill-B4{fill:#A6E2D0;}
		.d2-789827171 .fill-B5{fill:#CAF2E6;}
		.d2-789827171 .fill-B6{fill:#EBFDF7;}
		.d2-789827171 .fill-AA2{fill:#D35F0A;}
		.d2-789827171 .fill-AA4{fill:#FABA8A;}
		.d2-789827171 .fill-AA5{fill:#FFE0C7;}
		.d2-789827171 .fill-AB4{fill:#C9B9A1;}
		.d2-789827171 .fill-AB5{fill:#E9DBCA;}
		.d2-789827171 .stroke-N1{stroke:#170206;}
		.d2-789827171 .stroke-N2{stroke:#535152;}
		.d2-789827171 .stroke-N3{stroke:#787777;}
		.d2-789827171 .stroke-N4{stroke:#CCCACA;}
		.d2-789827171 .stroke-N5{stroke:#DFDCDC;}
		.d2-789827171 .stroke-N6{stroke:#ECEBEB;}
		.d2-789827171 .stroke-N7{stroke:#FFFFFF;}
		.d2-789827171 .stroke-B1{stroke:#023324;}
		.d2-789827171 .stroke-B2{stroke:#048E63;}
		.d2-789827171 .stroke-B3{stroke:#49BC99;}
		.d2-789827171 .stroke-B4{stroke:#A6E2D0;}
		.d2-789827171 .stroke-B5{stroke:#CAF2E6;}
		.d2-789827171 .stroke-B6{stroke:#EBFDF7;}
		.d2-789827171 .stroke-AA2{stroke:#D35F0A;}
		.d2-789827171 .stroke-AA4{stroke:#FABA8A;}
		.d2-789827171 .stroke-AA5{stroke:#FFE0C7;}
		.d2-789827171 .stroke-AB4{stroke:#C9B9A1;}
		.d2-789827171 .stroke-AB5{stroke:#E9DBCA;}
		.d2-789827171 .background-color-N1{background-color:#170206;}
		.d2-789827171 .background-color-N2{background-color:#535152;}
		.d2-789827171 .background-color-N3{background-color:#787777;}
		.d2-789827171 .background-color-N4{background-color:#CCCACA;}
		.d2-789827171 .background-color-N5{background-color:#DFDCDC;}
		.d2-789827171 .background-color-N6{background-color:#ECEBEB;}
		.d2-789827171 .background-color-N7{background-color:#FFFFFF;}
		.d2-789827171 .background-color-B1{background-color:#023324;}
		.d2-789827171 .background-color-B2{background-color:#048E63;}
		.d2-789827171 .background-color-B3{background-color:#49BC99;}
		.d2-789827171 .background-color-B4{background-color:#A6E2D0;}
		.d2-789827171 .background-color-B5{background-color:#CAF2E6;}
		.d2-789827171 .background-color-B6{background-color:#EBFDF7;}
		.d2-789827171 .background-color-AA2{background-color:#D35F0A;}
		.d2-789827171 .background-color-AA4{background-color:#FABA8A;}
		.d2-789827171 .background-color-AA5{background-color:#FFE0C7;}
		.d2-789827171 .background-color-AB4{background-color:#C9B9A1;}
		.d2-789827171 .background-color-AB5{background-color:#E9DBCA;}
		.d2-789827171 .color-N1{color:#170206;}
		.d2-789827171 .color-N2{color:#535152;}
		.d2-789827171 .color-N3{color:#787777;}
		.d2-789827171 .color-N4{color:#CCCACA;}
		.d2-789827171 .color-N5{color:#DFDCDC;}
		.d2-789827171 .color-N6{color:#ECEBEB;}
		.d2-789827171 .color-N7{color:#FFFFFF;}
		.d2-789827171 .color-B1{color:#023324;}
		.d2-789827171 .color-B2{color:#048E63;}
		.d2-789827171 .color-B3{color:#49BC99;}
		.d2-789827171 .color-B4{color:#A6E2D0;}
		.d2-789827171 .color-B5{color:#CAF2E6;}
		.d2-789827171 .color-B6{color:#EBFDF7;}
		.d2-789827171 .color-AA2{color:#D35F0A;}
		.d2-789827171 .color-AA4{color:#FABA8A;}
		.d2-789827171 .color-AA5{color:#FFE0C7;}
		.d2-789827171 .color-AB4{color:#C9B9A1;}
		.d2-789827171 .color-AB5{color:#E9DBCA;}.appendix text.text{fill:#170206}.md{--color-fg-default:#170206;--color-fg-muted:#535152;--color-fg-subtle:#787777;--color-canvas-default:#FFFFFF;--color-canvas-subtle:#ECEBEB;--color-border-default:#023324;--color-border-muted:#048E63;--color-neutral-muted:#ECEBEB;--color-accent-fg:#048E63;--color-accent-emphasis:#048E63;--color-attention-subtle:#535152;--color-danger-fg:red;}.sketch-overlay-B1{fill:url(#streaks-darker-d2-789827171);mix-blend-mode:lighten}.sketch-overlay-B2{fill:url(#streaks-dark-d2-789827171);mix-blend-mode:overlay}.sketch-overlay-B3{fill:url(#streaks-normal-d2-789827171);mix-blend-mode:color-burn}.sketch-overlay-B4{fill:url(#streaks-normal-d2-789827171);mix-blend-mode:color-burn}.sketch-overlay-B5{fill:url(#streaks-bright-d2-789827171);mix-blend-mode:darken}.sketch-overlay-B6{fill:url(#streaks-bright-d2-789827171);mix-blend-mode:darken}.sketch-overlay-AA2{fill:url(#streaks-dark-d2-789827171);mix-blend-mode:overlay}.sketch-overlay-AA4{fill:url(#streaks-normal-d2-789827171);mix-blend-mode:color-burn}.sketch-overlay-AA5{fill:url(#streaks-bright-d2-789827171);mix-blend-mode:darken}.sketch-overlay-AB4{fill:url(#streaks-normal-d2-789827171);mix-blend-mode:color-burn}.sketch-overlay-AB5{fill:url(#streaks-normal-d2-789827171);mix-blend-mode:color-burn}.sketch-overlay-N1{fill:url(#streaks-darker-d2-789827171);mix-blend-mode:lighten}.sketch-overlay-N2{fill:url(#streaks-dark-d2-789827171);mix-blend-mode:overlay}.sketch-overlay-N3{fill:url(#streaks-dark-d2-789827171);mix-blend-mode:overlay}.sketch-overlay-N4{fill:url(#streaks-normal-d2-789827171);mix-blend-mode:color-burn}.sketch-overlay-N5{fill:url(#streaks-normal-d2-789827171);mix-blend-mode:color-burn}.sketch-overlay-N6{fill:url(#streaks-bright-d2-789827171);mix-blend-mode:darken}.sketch-overlay-N7{fill:url(#streaks-bright-d2-789827171);mix-blend-mode:darken}.light-code{display: block}.dark-code{display: none}]]></style><g class="SVNlcnZlcg=="><g class="shape" ><rect x="53.000000" y="384.000000" width="97.000000" height="66.000000" stroke="#048E63" fill="#EBFDF7" class=" stroke-B2 fill-B6" style="stroke-width:2;stroke-dasharray:10.000000,9.865639;" /></g><text x="101.500000" y="422.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">IServer</text></g><g class="SVJlcXVlc3RIYW5kbGVy"><g class="shape" ><rect x="107.000000" y="784.000000" width="165.000000" height="66.000000" stroke="#048E63" fill="#EBFDF7" class=" stroke-B2 fill-B6" style="stroke-width:2;stroke-dasharray:10.000000,9.865639;" /></g><text x="189.500000" y="822.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">IRequestHandler</text></g><g class="SHR0cFNlcnZlcg=="><g class="shape" ><rect x="127.000000" y="192.000000" width="151.000000" height="66.000000" stroke="#023324" fill="#EBFDF7" class=" stroke-B1 fill-B6" style="stroke-width:2;" /></g><text x="202.500000" y="230.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">HTTP Сервер</text></g><g class="UHJveHlTZXJ2ZXI="><g class="shape" ><rect x="338.000000" y="192.000000" width="179.000000" height="66.000000" stroke="#023324" fill="#EBFDF7" class=" stroke-B1 fill-B6" style="stroke-width:2;" /></g><text x="427.500000" y="230.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">Прокси Сервер</text></g><g class="Um91dGVy"><g class="shape" ><rect x="308.000000" y="384.000000" width="187.000000" height="66.000000" stroke="#023324" fill="#EBFDF7" class=" stroke-B1 fill-B6" style="stroke-width:2;" /></g><text x="401.500000" y="422.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">Маршрутизатор</text></g><g class="U3RhdGljRmlsZUhhbmRsZXI="><g class="shape" ><rect x="143.000000" y="571.000000" width="348.000000" height="66.000000" stroke="#023324" fill="#EBFDF7" class=" stroke-B1 fill-B6" style="stroke-width:2;" /></g><text x="317.000000" y="609.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">Обработчик Статических Файлов</text></g><g class="VGNwUHJveHk="><g class="shape" ><rect x="595.000000" y="571.000000" width="142.000000" height="66.000000" stroke="#023324" fill="#EBFDF7" class=" stroke-B1 fill-B6" style="stroke-width:2;" /></g><text x="666.000000" y="609.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">TCP Прокси</text></g><g class="Q29uZmlnTG9hZGVy"><g class="shape" ><rect x="534.000000" y="0.000000" width="279.000000" height="66.000000" stroke="#023324" fill="#EBFDF7" class=" stroke-B1 fill-B6" style="stroke-width:2;" /></g><text x="673.500000" y="38.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">Загрузчик Конфигурации</text></g><g class="Q29uZmln"><g class="shape" ><path d="M 585 252 L 585 187 L 761 187 L 761 252 C 732 238 702 238 673 252 C 644 267 614 267 585 252 Z" stroke="#023324" fill="#C9B9A1" class=" stroke-B1 fill-AB4" style="stroke-width:2;" /></g><text x="673.000000" y="220.610964" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">Конфигурация</text></g><g class="TG9nZ2Vy"><g class="shape" ><rect x="260.000000" y="0.000000" width="110.000000" height="66.000000" stroke="#023324" fill="#EBFDF7" class=" stroke-B1 fill-B6" style="stroke-width:2;" /></g><text x="315.000000" y="38.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">Логгер</text></g><g class="RmlsZVN5c3RlbQ=="><g class="shape" ><path d="M 406 782 C 406 758 506 758 518 758 C 529 758 629 758 629 782 V 852 C 629 876 529 876 518 876 C 506 876 406 876 406 852 V 782 Z" stroke="#023324" fill="#FABA8A" class=" stroke-B1 fill-AA4" style="stroke-width:2;" /><path d="M 406 782 C 406 806 506 806 518 806 C 529 806 629 806 629 782" stroke="#023324" fill="#FABA8A" class=" stroke-B1 fill-AA4" style="stroke-width:2;" /></g><text x="517.500000" y="834.500000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">Статические Файлы</text></g><g class="UmVtb3RlU2VydmVy"><g class="shape" ><path d="M 777 804 C 777 805 775 806 773 806 C 750 807 732 818 732 832 C 732 847 752 859 778 859 H 954 C 982 859 1004 846 1004 831 C 1004 816 983 804 957 803 C 955 803 953 802 953 801 C 947 786 920 775 888 775 C 867 775 848 780 837 787 C 836 788 833 788 832 788 C 827 787 822 787 817 787 C 796 787 779 794 777 804 Z" stroke="#023324" fill="#FFFFFF" class=" stroke-B1 fill-N7" style="stroke-width:2;" /></g><text x="867.793500" y="838.516000" fill="#170206" class="text-bold fill-N1" style="text-anchor:middle;font-size:16px">Удаленные Серверы</text></g><g class="KElTZXJ2ZXIgJmx0Oy0gSHR0cFNlcnZlcilbMF0="><marker id="mk-d2-789827171-2451250203" markerWidth="10.000000" markerHeight="12.000000" refX="3.000000" refY="6.000000" viewBox="0.000000 0.000000 10.000000 12.000000" orient="auto" markerUnits="userSpaceOnUse"> <polygon points="10.000000,0.000000 0.000000,6.000000 10.000000,12.000000" fill="#023324" class="connection fill-B1" stroke-width="2" /> </marker><path d="M 79.466985 381.055170 C 52.700001 335.700012 66.099998 310.299988 146.816051 258.579035" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-start="url(#mk-d2-789827171-2451250203)" mask="url(#d2-789827171)" /><text x="71.500000" y="312.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">реализует</text></g><g class="KElTZXJ2ZXIgJmx0Oy0gUHJveHlTZXJ2ZXIpWzBd"><path d="M 143.569436 381.935129 C 198.899994 335.700012 241.699997 310.299988 352.688619 258.347880" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-start="url(#mk-d2-789827171-2451250203)" mask="url(#d2-789827171)" /><text x="241.500000" y="316.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">реализует</text></g><g class="KElSZXF1ZXN0SGFuZGxlciAmbHQ7LSBTdGF0aWNGaWxlSGFuZGxlcilbMF0="><path d="M 172.329067 780.865721 C 142.000000 714.900024 157.399994 685.299988 249.226560 637.424614" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-start="url(#mk-d2-789827171-2451250203)" mask="url(#d2-789827171)" /><text x="156.500000" y="693.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">реализует</text></g><g class="KElSZXF1ZXN0SGFuZGxlciAmbHQ7LSBUY3BQcm94eSlbMF0="><path d="M 235.137340 782.018650 C 320.000000 714.900024 392.600006 682.900024 593.078392 625.054456" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-start="url(#mk-d2-789827171-2451250203)" mask="url(#d2-789827171)" /><text x="401.500000" y="686.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">реализует</text></g><g class="KEh0dHBTZXJ2ZXIgLSZndDsgUm91dGVyKVswXQ=="><marker id="mk-d2-789827171-3488378134" markerWidth="10.000000" markerHeight="12.000000" refX="7.000000" refY="6.000000" viewBox="0.000000 0.000000 10.000000 12.000000" orient="auto" markerUnits="userSpaceOnUse"> <polygon points="0.000000,0.000000 10.000000,6.000000 0.000000,12.000000" fill="#023324" class="connection fill-B1" stroke-width="2" /> </marker><path d="M 270.788854 258.394427 C 374.600006 310.299988 401.000000 335.700012 401.000000 380.500000" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-end="url(#mk-d2-789827171-3488378134)" mask="url(#d2-789827171)" /><text x="360.500000" y="309.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">маршрутизирует запросы</text></g><g class="KFJvdXRlciAtJmd0OyBTdGF0aWNGaWxlSGFuZGxlcilbMF0="><path d="M 370.160726 450.985377 C 327.500000 498.299988 316.500000 522.700012 316.500000 567.500000" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-end="url(#mk-d2-789827171-3488378134)" mask="url(#d2-789827171)" /><text x="325.000000" y="508.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">статические файлы</text></g><g class="KFJvdXRlciAtJmd0OyBUY3BQcm94eSlbMF0="><path d="M 456.202726 450.549154 C 533.700012 498.299988 567.900024 522.700012 622.448063 568.914331" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-end="url(#mk-d2-789827171-3488378134)" mask="url(#d2-789827171)" /><text x="544.000000" y="511.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">прокси запросы</text></g><g class="KFByb3h5U2VydmVyIC0mZ3Q7IFRjcFByb3h5KVswXQ=="><path d="M 519.387429 256.867515 C 671.099976 310.040985 709.500000 342.200012 709.500000 370.250000 C 709.500000 398.299988 703.900024 522.700012 683.168672 567.864683" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-end="url(#mk-d2-789827171-3488378134)" mask="url(#d2-789827171)" /><text x="709.500000" y="358.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">использует</text></g><g class="KENvbmZpZ0xvYWRlciAtJmd0OyBDb25maWcpWzBd"><path d="M 673.000000 67.500000 C 673.000000 114.300003 673.000000 138.600006 673.000000 183.000000" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-end="url(#mk-d2-789827171-3488378134)" mask="url(#d2-789827171)" /><text x="673.500000" y="132.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">загружает</text></g><g class="KExvZ2dlciAtJmd0OyBIdHRwU2VydmVyKVswXQ=="><path d="M 273.465282 66.782436 C 216.600006 114.300003 202.000000 139.699997 202.000000 188.500000" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-end="url(#mk-d2-789827171-3488378134)" mask="url(#d2-789827171)" /><text x="215.500000" y="122.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">логирует</text></g><g class="KExvZ2dlciAtJmd0OyBQcm94eVNlcnZlcilbMF0="><path d="M 355.534718 66.782436 C 412.399994 114.300003 427.000000 139.699997 427.000000 188.500000" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-end="url(#mk-d2-789827171-3488378134)" mask="url(#d2-789827171)" /><text x="413.500000" y="122.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">логирует</text></g><g class="KFN0YXRpY0ZpbGVIYW5kbGVyIC0mZ3Q7IEZpbGVTeXN0ZW0pWzBd"><path d="M 388.810583 637.349581 C 491.000000 685.299988 517.000000 709.599976 517.000000 754.000000" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-end="url(#mk-d2-789827171-3488378134)" mask="url(#d2-789827171)" /><text x="477.500000" y="684.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">читает</text></g><g class="KFRjcFByb3h5IC0mZ3Q7IFJlbW90ZVNlcnZlcilbMF0="><path d="M 738.813073 637.344255 C 841.799988 685.299988 868.000000 713.400024 868.000000 773.000000" stroke="#023324" fill="none" class="connection stroke-B1" style="stroke-width:2;" marker-end="url(#mk-d2-789827171-3488378134)" mask="url(#d2-789827171)" /><text x="835.500000" y="688.000000" fill="#535152" class="text-italic fill-N2" style="text-anchor:middle;font-size:16px">перенаправляет</text></g><mask id="d2-789827171" maskUnits="userSpaceOnUse" x="-74" y="-101" width="1180" height="1078">
<rect x="-74" y="-101" width="1180" height="1078" fill="white"></rect>
<rect x="75.500000" y="406.500000" width="52" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="129.500000" y="806.500000" width="120" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="149.500000" y="214.500000" width="106" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="360.500000" y="214.500000" width="134" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="330.500000" y="406.500000" width="142" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="165.500000" y="593.500000" width="303" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="617.500000" y="593.500000" width="97" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="556.500000" y="22.500000" width="234" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="607.500000" y="204.610964" width="131" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="282.500000" y="22.500000" width="65" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="428.500000" y="818.500000" width="178" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="778.793500" y="822.516000" width="178" height="21" fill="rgba(0,0,0,0.75)"></rect>
<rect x="26.000000" y="296.000000" width="91" height="21" fill="black"></rect>
<rect x="196.000000" y="300.000000" width="91" height="21" fill="black"></rect>
<rect x="111.000000" y="677.000000" width="91" height="21" fill="black"></rect>
<rect x="356.000000" y="670.000000" width="91" height="21" fill="black"></rect>
<rect x="253.000000" y="293.000000" width="215" height="21" fill="black"></rect>
<rect x="243.000000" y="492.000000" width="164" height="21" fill="black"></rect>
<rect x="477.000000" y="495.000000" width="134" height="21" fill="black"></rect>
<rect x="659.000000" y="342.000000" width="101" height="21" fill="black"></rect>
<rect x="628.000000" y="116.000000" width="91" height="21" fill="black"></rect>
<rect x="175.000000" y="106.000000" width="81" height="21" fill="black"></rect>
<rect x="373.000000" y="106.000000" width="81" height="21" fill="black"></rect>
<rect x="447.000000" y="668.000000" width="61" height="21" fill="black"></rect>
<rect x="765.000000" y="672.000000" width="141" height="21" fill="black"></rect>
</mask></svg></svg>[Uploading d2.svg…]()

## Возможности

- **HTTP-сервер**: Полная поддержка HTTP/1.1 с асинхронной обработкой запросов
- **Маршрутизация**: Гибкая система маршрутизации HTTP-запросов с различными типами обработчиков
- **Прокси-сервер**: Перенаправление запросов на другие серверы
- **Статические файлы**: Отдача статических файлов из указанной директории
- **Многопоточность**: Эффективная обработка запросов с использованием нескольких потоков

## Требования

- C++20 совместимый компилятор (GCC 10+, Clang 10+, MSVC 2019+)
- CMake 3.15 или выше
- Boost 1.75.0 или выше

## Сборка

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Запуск

```bash
./Hermes
```

## Типы маршрутов

Hermes поддерживает следующие типы маршрутов:

1. **static** - Статический контент, определенный в конфигурации
2. **json** - JSON-ответы
3. **text** - Текстовые ответы
4. **proxy** - Перенаправление запросов на другой сервер

## Архитектура

Hermes построен на модульной архитектуре с четким разделением ответственности:

- **Config** - Загрузка и хранение конфигурации
- **Logger** - Простая система логирования
- **Router** - Маршрутизация HTTP-запросов к соответствующим обработчикам
- **HttpServer** - Обработка HTTP-соединений с использованием Boost.Beast
- **ProxyServer** - Перенаправление HTTP-запросов на внешние серверы
- **StaticFileHandler** - Отдача статических файлов из директории

## Особенности реализации

- Асинхронная обработка запросов для высокой производительности
- Эффективное использование пула потоков для параллельной обработки запросов
- Корректная обработка сигналов для graceful shutdown
- Четкое разделение между HTTP и TCP обработкой

## Использование для разработки

Сервер можно использовать для:
- Быстрого прототипирования веб-приложений
- Реализации API-серверов
- Создания прокси-серверов
- Низкоуровневых TCP-служб
- Балансировки нагрузки

## Лицензия

Свободно распространяемое ПО. Используйте на свой страх и риск.

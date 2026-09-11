 800cdd8:	4770      	bx	lr
 800cdda:	b508      	push	{r3, lr}
 800cddc:	2001      	movs	r0, #1
 800cdde:	f000 ff41 	bl	0x800dc64
 800cde2:	2001      	movs	r0, #1
 800cde4:	2103      	movs	r1, #3
 800cde6:	f001 fb8d 	bl	0x800e504
 800cdea:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
 800cdee:	2001      	movs	r0, #1
 800cdf0:	f001 bbaa 	b.w	0x800e548
 800cdf4:	22ff      	movs	r2, #255	@ 0xff
 800cdf6:	2100      	movs	r1, #0
 800cdf8:	4610      	mov	r0, r2
 800cdfa:	f003 b873 	b.w	0x800fee4
 800cdfe:	2200      	movs	r2, #0
 800ce00:	b508      	push	{r3, lr}
 800ce02:	4610      	mov	r0, r2
 800ce04:	4611      	mov	r1, r2
 800ce06:	f003 f86d 	bl	0x800fee4
 800ce0a:	2009      	movs	r0, #9
 800ce0c:	f004 fe16 	bl	0x8011a3c
 800ce10:	b1b8      	cbz	r0, 0x800ce42
 800ce12:	20e3      	movs	r0, #227	@ 0xe3
 800ce14:	f000 fbac 	bl	0x800d570
 800ce18:	2013      	movs	r0, #19
 800ce1a:	f000 fba9 	bl	0x800d570
 800ce1e:	20e3      	movs	r0, #227	@ 0xe3
 800ce20:	f000 fbee 	bl	0x800d600
 800ce24:	2013      	movs	r0, #19
 800ce26:	f000 fbeb 	bl	0x800d600
 800ce2a:	20e3      	movs	r0, #227	@ 0xe3
 800ce2c:	f000 fba0 	bl	0x800d570
 800ce30:	200e      	movs	r0, #14
 800ce32:	f000 fb9d 	bl	0x800d570
 800ce36:	20e3      	movs	r0, #227	@ 0xe3
 800ce38:	f000 fbe2 	bl	0x800d600
 800ce3c:	200e      	movs	r0, #14
 800ce3e:	f000 fbdf 	bl	0x800d600
 800ce42:	2114      	movs	r1, #20
 800ce44:	2004      	movs	r0, #4
 800ce46:	f004 fe03 	bl	0x8011a50
 800ce4a:	b1e8      	cbz	r0, 0x800ce88
 800ce4c:	20e0      	movs	r0, #224	@ 0xe0
 800ce4e:	f000 fb8f 	bl	0x800d570
 800ce52:	2004      	movs	r0, #4
 800ce54:	f000 fb8c 	bl	0x800d570
 800ce58:	20e0      	movs	r0, #224	@ 0xe0
 800ce5a:	f000 fbd1 	bl	0x800d600
 800ce5e:	2004      	movs	r0, #4
 800ce60:	f000 fbce 	bl	0x800d600
 800ce64:	201d      	movs	r0, #29
 800ce66:	f000 fb83 	bl	0x800d570
 800ce6a:	201d      	movs	r0, #29
 800ce6c:	f000 fbc8 	bl	0x800d600
 800ce70:	2014      	movs	r0, #20
 800ce72:	f000 fb7d 	bl	0x800d570
 800ce76:	2014      	movs	r0, #20
 800ce78:	f000 fbc2 	bl	0x800d600
 800ce7c:	2028      	movs	r0, #40	@ 0x28
 800ce7e:	f000 fb77 	bl	0x800d570
 800ce82:	2028      	movs	r0, #40	@ 0x28
 800ce84:	f000 fbbc 	bl	0x800d600
 800ce88:	201c      	movs	r0, #28
 800ce8a:	f004 fdd7 	bl	0x8011a3c
 800ce8e:	b1b8      	cbz	r0, 0x800cec0
 800ce90:	20e0      	movs	r0, #224	@ 0xe0
 800ce92:	f000 fb6d 	bl	0x800d570
 800ce96:	201b      	movs	r0, #27
 800ce98:	f000 fb6a 	bl	0x800d570
 800ce9c:	20e0      	movs	r0, #224	@ 0xe0
 800ce9e:	f000 fbaf 	bl	0x800d600
 800cea2:	201b      	movs	r0, #27
 800cea4:	f000 fbac 	bl	0x800d600
 800cea8:	201c      	movs	r0, #28
 800ceaa:	f000 fb61 	bl	0x800d570
 800ceae:	201c      	movs	r0, #28
 800ceb0:	f000 fba6 	bl	0x800d600
 800ceb4:	2028      	movs	r0, #40	@ 0x28
 800ceb6:	f000 fb5b 	bl	0x800d570
 800ceba:	2028      	movs	r0, #40	@ 0x28
 800cebc:	f000 fba0 	bl	0x800d600
 800cec0:	210c      	movs	r1, #12
 800cec2:	20e0      	movs	r0, #224	@ 0xe0
 800cec4:	f004 fdc4 	bl	0x8011a50
 800cec8:	b188      	cbz	r0, 0x800ceee
 800ceca:	20e0      	movs	r0, #224	@ 0xe0
 800cecc:	f000 fb50 	bl	0x800d570
 800ced0:	20e2      	movs	r0, #226	@ 0xe2
 800ced2:	f000 fb4d 	bl	0x800d570
 800ced6:	200c      	movs	r0, #12
 800ced8:	f000 fb4a 	bl	0x800d570
 800cedc:	20e0      	movs	r0, #224	@ 0xe0
 800cede:	f000 fb8f 	bl	0x800d600
 800cee2:	20e2      	movs	r0, #226	@ 0xe2
 800cee4:	f000 fb8c 	bl	0x800d600
 800cee8:	200c      	movs	r0, #12
 800ceea:	f000 fb89 	bl	0x800d600
 800ceee:	200d      	movs	r0, #13
 800cef0:	f004 fda4 	bl	0x8011a3c
 800cef4:	b158      	cbz	r0, 0x800cf0e
 800cef6:	20e3      	movs	r0, #227	@ 0xe3
 800cef8:	f000 fb3a 	bl	0x800d570
 800cefc:	2013      	movs	r0, #19
 800cefe:	f000 fb37 	bl	0x800d570
 800cf02:	20e3      	movs	r0, #227	@ 0xe3
 800cf04:	f000 fb7c 	bl	0x800d600
 800cf08:	2013      	movs	r0, #19
 800cf0a:	f000 fb79 	bl	0x800d600
 800cf0e:	2009      	movs	r0, #9
 800cf10:	f004 fd94 	bl	0x8011a3c
 800cf14:	b158      	cbz	r0, 0x800cf2e
 800cf16:	20e3      	movs	r0, #227	@ 0xe3
 800cf18:	f000 fb2a 	bl	0x800d570
 800cf1c:	2034      	movs	r0, #52	@ 0x34
 800cf1e:	f000 fb27 	bl	0x800d570
 800cf22:	20e3      	movs	r0, #227	@ 0xe3
 800cf24:	f000 fb6c 	bl	0x800d600
 800cf28:	2034      	movs	r0, #52	@ 0x34
 800cf2a:	f000 fb69 	bl	0x800d600
 800cf2e:	204c      	movs	r0, #76	@ 0x4c
 800cf30:	f004 fd84 	bl	0x8011a3c
 800cf34:	b198      	cbz	r0, 0x800cf5e
 800cf36:	20e3      	movs	r0, #227	@ 0xe3
 800cf38:	f000 fb1a 	bl	0x800d570
 800cf3c:	2052      	movs	r0, #82	@ 0x52
 800cf3e:	f000 fb17 	bl	0x800d570
 800cf42:	2050      	movs	r0, #80	@ 0x50
 800cf44:	f000 fb14 	bl	0x800d570
 800cf48:	20e3      	movs	r0, #227	@ 0xe3
 800cf4a:	f000 fb59 	bl	0x800d600
 800cf4e:	2052      	movs	r0, #82	@ 0x52
 800cf50:	f000 fb56 	bl	0x800d600
 800cf54:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
 800cf58:	2050      	movs	r0, #80	@ 0x50
 800cf5a:	f000 bb51 	b.w	0x800d600
 800cf5e:	bd08      	pop	{r3, pc}
 800cf60:	b508      	push	{r3, lr}
 800cf62:	2000      	movs	r0, #0
 800cf64:	f000 fe3d 	bl	0x800dbe2
 800cf68:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
 800cf6c:	2010      	movs	r0, #16
 800cf6e:	f003 bee7 	b.w	0x8010d40
 800cf72:	0000      	movs	r0, r0
 800cf74:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
 800cf78:	4e20      	ldr	r6, [pc, #128]	@ (0x800cffc)
 800cf7a:	4f21      	ldr	r7, [pc, #132]	@ (0x800d000)
 800cf7c:	f8df 808c 	ldr.w	r8, [pc, #140]	@ 0x800d00c
 800cf80:	460d      	mov	r5, r1
 800cf82:	4604      	mov	r4, r0
 800cf84:	b2e3      	uxtb	r3, r4
 800cf86:	429d      	cmp	r5, r3
 800cf88:	d802      	bhi.n	0x800cf90
 800cf8a:	2000      	movs	r0, #0
 800cf8c:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
 800cf90:	8830      	ldrh	r0, [r6, #0]
 800cf92:	883b      	ldrh	r3, [r7, #0]
 800cf94:	4318      	orrs	r0, r3
 800cf96:	b280      	uxth	r0, r0
 800cf98:	f000 fa76 	bl	0x800d488
 800cf9c:	3801      	subs	r0, #1
 800cf9e:	2804      	cmp	r0, #4
 800cfa0:	d80a      	bhi.n	0x800cfb8
 800cfa2:	e8df f000 	tbb	[pc, r0]
 800cfa6:	0318      	lsls	r0, r3, #12
 800cfa8:	1b14      	subs	r4, r2, r4
 800cfaa:	001e      	movs	r6, r3
 800cfac:	23ff      	movs	r3, #255	@ 0xff
 800cfae:	2200      	movs	r2, #0
 800cfb0:	2100      	movs	r1, #0
 800cfb2:	4620      	mov	r0, r4
 800cfb4:	f002 ff60 	bl	0x800fe78
 800cfb8:	f898 3000 	ldrb.w	r3, [r8]
 800cfbc:	b1a3      	cbz	r3, 0x800cfe8
 800cfbe:	22ff      	movs	r2, #255	@ 0xff
 800cfc0:	2300      	movs	r3, #0
 800cfc2:	4611      	mov	r1, r2
 800cfc4:	4620      	mov	r0, r4
 800cfc6:	f002 ff57 	bl	0x800fe78
 800cfca:	3401      	adds	r4, #1
 800cfcc:	e7da      	b.n	0x800cf84
 800cfce:	2300      	movs	r3, #0
 800cfd0:	2280      	movs	r2, #128	@ 0x80
 800cfd2:	21ff      	movs	r1, #255	@ 0xff
 800cfd4:	e7ed      	b.n	0x800cfb2
 800cfd6:	2300      	movs	r3, #0
 800cfd8:	22ff      	movs	r2, #255	@ 0xff
 800cfda:	e7e9      	b.n	0x800cfb0
 800cfdc:	2380      	movs	r3, #128	@ 0x80
 800cfde:	461a      	mov	r2, r3
 800cfe0:	e7e6      	b.n	0x800cfb0
 800cfe2:	2300      	movs	r3, #0
 800cfe4:	461a      	mov	r2, r3
 800cfe6:	e7f4      	b.n	0x800cfd2
 800cfe8:	4b06      	ldr	r3, [pc, #24]	@ (0x800d004)
 800cfea:	4a07      	ldr	r2, [pc, #28]	@ (0x800d008)
 800cfec:	781b      	ldrb	r3, [r3, #0]
 800cfee:	7812      	ldrb	r2, [r2, #0]
 800cff0:	4313      	orrs	r3, r2
 800cff2:	d0ea      	beq.n	0x800cfca
 800cff4:	23ff      	movs	r3, #255	@ 0xff
 800cff6:	461a      	mov	r2, r3
 800cff8:	4619      	mov	r1, r3
 800cffa:	e7e3      	b.n	0x800cfc4
 800cffc:	162e      	asrs	r6, r5, #24
 800cffe:	2000      	movs	r0, #0
 800d000:	1630      	asrs	r0, r6, #24
 800d002:	2000      	movs	r0, #0
 800d004:	15de      	asrs	r6, r3, #23
 800d006:	2000      	movs	r0, #0
 800d008:	15dc      	asrs	r4, r3, #23
 800d00a:	2000      	movs	r0, #0
 800d00c:	15dd      	asrs	r5, r3, #23
 800d00e:	2000      	movs	r0, #0
 800d010:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 800d012:	f010 0522 	ands.w	r5, r0, #34	@ 0x22
 800d016:	f020 0477 	bic.w	r4, r0, #119	@ 0x77
 800d01a:	d113      	bne.n	0x800d044
 800d01c:	4e18      	ldr	r6, [pc, #96]	@ (0x800d080)
 800d01e:	7833      	ldrb	r3, [r6, #0]
 800d020:	b183      	cbz	r3, 0x800d044
 800d022:	462a      	mov	r2, r5
 800d024:	4629      	mov	r1, r5
 800d026:	4628      	mov	r0, r5
 800d028:	f002 ff5c 	bl	0x800fee4
 800d02c:	7035      	strb	r5, [r6, #0]
 800d02e:	b144      	cbz	r4, 0x800d042
 800d030:	4c14      	ldr	r4, [pc, #80]	@ (0x800d084)
 800d032:	7822      	ldrb	r2, [r4, #0]
 800d034:	b92a      	cbnz	r2, 0x800d042
 800d036:	21ff      	movs	r1, #255	@ 0xff
 800d038:	4608      	mov	r0, r1
 800d03a:	f002 ff53 	bl	0x800fee4
 800d03e:	2301      	movs	r3, #1
 800d040:	7023      	strb	r3, [r4, #0]
 800d042:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
 800d044:	f004 06ff 	and.w	r6, r4, #255	@ 0xff
 800d048:	b9b4      	cbnz	r4, 0x800d078
 800d04a:	4f0e      	ldr	r7, [pc, #56]	@ (0x800d084)
 800d04c:	783b      	ldrb	r3, [r7, #0]
 800d04e:	b12b      	cbz	r3, 0x800d05c
 800d050:	4632      	mov	r2, r6
 800d052:	4631      	mov	r1, r6
 800d054:	4630      	mov	r0, r6
 800d056:	f002 ff45 	bl	0x800fee4
 800d05a:	703e      	strb	r6, [r7, #0]
 800d05c:	2d00      	cmp	r5, #0
 800d05e:	d0f0      	beq.n	0x800d042
 800d060:	4d07      	ldr	r5, [pc, #28]	@ (0x800d080)
 800d062:	782b      	ldrb	r3, [r5, #0]
 800d064:	2b00      	cmp	r3, #0
 800d066:	d1e2      	bne.n	0x800d02e
 800d068:	22ff      	movs	r2, #255	@ 0xff
 800d06a:	4611      	mov	r1, r2
 800d06c:	4610      	mov	r0, r2
 800d06e:	f002 ff39 	bl	0x800fee4
 800d072:	2301      	movs	r3, #1
 800d074:	702b      	strb	r3, [r5, #0]
 800d076:	e7da      	b.n	0x800d02e
 800d078:	2d00      	cmp	r5, #0
 800d07a:	d1f1      	bne.n	0x800d060
 800d07c:	e7d8      	b.n	0x800d030
 800d07e:	bf00      	nop
 800d080:	15de      	asrs	r6, r3, #23
 800d082:	2000      	movs	r0, #0
 800d084:	15dd      	asrs	r5, r3, #23
 800d086:	2000      	movs	r0, #0
 800d088:	f7ff bfc2 	b.w	0x800d010
 800d08c:	f7ff bfc0 	b.w	0x800d010
 800d090:	4a07      	ldr	r2, [pc, #28]	@ (0x800d0b0)
 800d092:	4603      	mov	r3, r0
 800d094:	6810      	ldr	r0, [r2, #0]
 800d096:	b148      	cbz	r0, 0x800d0ac
 800d098:	8802      	ldrh	r2, [r0, #0]
 800d09a:	429a      	cmp	r2, r3
 800d09c:	d005      	beq.n	0x800d0aa
 800d09e:	1d02      	adds	r2, r0, #4
 800d0a0:	8881      	ldrh	r1, [r0, #4]
 800d0a2:	4299      	cmp	r1, r3
 800d0a4:	bf0c      	ite	eq
 800d0a6:	4610      	moveq	r0, r2
 800d0a8:	2000      	movne	r0, #0
 800d0aa:	4770      	bx	lr
 800d0ac:	2204      	movs	r2, #4
 800d0ae:	e7f7      	b.n	0x800d0a0
 800d0b0:	15e0      	asrs	r0, r4, #23
 800d0b2:	2000      	movs	r0, #0
 800d0b4:	b538      	push	{r3, r4, r5, lr}
 800d0b6:	4605      	mov	r5, r0
 800d0b8:	f7ff ffea 	bl	0x800d090
 800d0bc:	4604      	mov	r4, r0
 800d0be:	b1c0      	cbz	r0, 0x800d0f2
 800d0c0:	f001 f926 	bl	0x800e310
 800d0c4:	b908      	cbnz	r0, 0x800d0ca
 800d0c6:	2000      	movs	r0, #0
 800d0c8:	bd38      	pop	{r3, r4, r5, pc}
 800d0ca:	8823      	ldrh	r3, [r4, #0]
 800d0cc:	42ab      	cmp	r3, r5
 800d0ce:	d0fa      	beq.n	0x800d0c6
 800d0d0:	f001 f9a8 	bl	0x800e424
 800d0d4:	f001 f96c 	bl	0x800e3b0
 800d0d8:	f001 f952 	bl	0x800e380
 800d0dc:	f000 fad2 	bl	0x800d684
 800d0e0:	4a05      	ldr	r2, [pc, #20]	@ (0x800d0f8)
 800d0e2:	2300      	movs	r3, #0
 800d0e4:	6013      	str	r3, [r2, #0]
 800d0e6:	6053      	str	r3, [r2, #4]
 800d0e8:	4a04      	ldr	r2, [pc, #16]	@ (0x800d0fc)
 800d0ea:	7013      	strb	r3, [r2, #0]
 800d0ec:	4a04      	ldr	r2, [pc, #16]	@ (0x800d100)
 800d0ee:	7013      	strb	r3, [r2, #0]
 800d0f0:	e7e9      	b.n	0x800d0c6
 800d0f2:	2001      	movs	r0, #1
 800d0f4:	e7e8      	b.n	0x800d0c8
 800d0f6:	bf00      	nop
 800d0f8:	15e0      	asrs	r0, r4, #23
 800d0fa:	2000      	movs	r0, #0
 800d0fc:	15de      	asrs	r6, r3, #23
 800d0fe:	2000      	movs	r0, #0
 800d100:	15dd      	asrs	r5, r3, #23
 800d102:	2000      	movs	r0, #0
 800d104:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 800d106:	4604      	mov	r4, r0
 800d108:	460e      	mov	r6, r1
 800d10a:	f7ff fb09 	bl	0x800c720
 800d10e:	4605      	mov	r5, r0
 800d110:	2800      	cmp	r0, #0
 800d112:	d044      	beq.n	0x800d19e
 800d114:	4b28      	ldr	r3, [pc, #160]	@ (0x800d1b8)
 800d116:	781a      	ldrb	r2, [r3, #0]
 800d118:	b122      	cbz	r2, 0x800d124
 800d11a:	f5b4 4fae 	cmp.w	r4, #22272	@ 0x5700
 800d11e:	bf1c      	itt	ne
 800d120:	2200      	movne	r2, #0
 800d122:	701a      	strbne	r2, [r3, #0]
 800d124:	4f25      	ldr	r7, [pc, #148]	@ (0x800d1bc)
 800d126:	783b      	ldrb	r3, [r7, #0]
 800d128:	b123      	cbz	r3, 0x800d134
 800d12a:	2001      	movs	r0, #1
 800d12c:	f000 fd86 	bl	0x800dc3c
 800d130:	b900      	cbnz	r0, 0x800d134
 800d132:	7038      	strb	r0, [r7, #0]
 800d134:	7973      	ldrb	r3, [r6, #5]
 800d136:	b1cb      	cbz	r3, 0x800d16c
 800d138:	2c39      	cmp	r4, #57	@ 0x39
 800d13a:	d010      	beq.n	0x800d15e
 800d13c:	f5a4 43a5 	sub.w	r3, r4, #21120	@ 0x5280
 800d140:	3b22      	subs	r3, #34	@ 0x22
 800d142:	b29b      	uxth	r3, r3
 800d144:	2b16      	cmp	r3, #22
 800d146:	d81a      	bhi.n	0x800d17e
 800d148:	f04f 1241 	mov.w	r2, #4259905	@ 0x410041
 800d14c:	fa22 f303 	lsr.w	r3, r2, r3
 800d150:	07d9      	lsls	r1, r3, #31
 800d152:	d50b      	bpl.n	0x800d16c
 800d154:	4620      	mov	r0, r4
 800d156:	e8bd 40f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, lr}
 800d15a:	f7ff bfab 	b.w	0x800d0b4
 800d15e:	f004 fff3 	bl	0x8012148
 800d162:	0782      	lsls	r2, r0, #30
 800d164:	d404      	bmi.n	0x800d170
 800d166:	4b16      	ldr	r3, [pc, #88]	@ (0x800d1c0)
 800d168:	2201      	movs	r2, #1
 800d16a:	701a      	strb	r2, [r3, #0]
 800d16c:	4628      	mov	r0, r5
 800d16e:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
 800d170:	f004 ffea 	bl	0x8012148
 800d174:	0783      	lsls	r3, r0, #30
 800d176:	d5f9      	bpl.n	0x800d16c
 800d178:	4b11      	ldr	r3, [pc, #68]	@ (0x800d1c0)
 800d17a:	2200      	movs	r2, #0
 800d17c:	e7f5      	b.n	0x800d16a
 800d17e:	f647 6340 	movw	r3, #32320	@ 0x7e40
 800d182:	429c      	cmp	r4, r3
 800d184:	d10d      	bne.n	0x800d1a2
 800d186:	2037      	movs	r0, #55	@ 0x37
 800d188:	f000 f9f2 	bl	0x800d570
 800d18c:	2037      	movs	r0, #55	@ 0x37
 800d18e:	f000 fa37 	bl	0x800d600
 800d192:	2038      	movs	r0, #56	@ 0x38
 800d194:	f000 f9ec 	bl	0x800d570
 800d198:	2038      	movs	r0, #56	@ 0x38
 800d19a:	f000 fa31 	bl	0x800d600
 800d19e:	2500      	movs	r5, #0
 800d1a0:	e7e4      	b.n	0x800d16c
 800d1a2:	f647 6341 	movw	r3, #32321	@ 0x7e41
 800d1a6:	429c      	cmp	r4, r3
 800d1a8:	d1e0      	bne.n	0x800d16c
 800d1aa:	2037      	movs	r0, #55	@ 0x37
 800d1ac:	f000 f9e0 	bl	0x800d570
 800d1b0:	2037      	movs	r0, #55	@ 0x37
 800d1b2:	f000 fa25 	bl	0x800d600
 800d1b6:	e7e6      	b.n	0x800d186
 800d1b8:	15e8      	asrs	r0, r5, #23
 800d1ba:	2000      	movs	r0, #0
 800d1bc:	15e9      	asrs	r1, r5, #23
 800d1be:	2000      	movs	r0, #0
 800d1c0:	15dc      	asrs	r4, r3, #23
 800d1c2:	2000      	movs	r0, #0
 800d1c4:	7883      	ldrb	r3, [r0, #2]
 800d1c6:	2b01      	cmp	r3, #1
 800d1c8:	d108      	bne.n	0x800d1dc
 800d1ca:	7943      	ldrb	r3, [r0, #5]
 800d1cc:	07da      	lsls	r2, r3, #31
 800d1ce:	d50a      	bpl.n	0x800d1e6
 800d1d0:	f013 0f04 	tst.w	r3, #4
 800d1d4:	bf0c      	ite	eq
 800d1d6:	2003      	moveq	r0, #3
 800d1d8:	2001      	movne	r0, #1
 800d1da:	4770      	bx	lr
 800d1dc:	2b02      	cmp	r3, #2
 800d1de:	bf0c      	ite	eq
 800d1e0:	2004      	moveq	r0, #4
 800d1e2:	2001      	movne	r0, #1
 800d1e4:	4770      	bx	lr
 800d1e6:	2002      	movs	r0, #2
 800d1e8:	4770      	bx	lr
 800d1ea:	0000      	movs	r0, r0
 800d1ec:	b538      	push	{r3, r4, r5, lr}
 800d1ee:	f7ff ffe9 	bl	0x800d1c4
 800d1f2:	2803      	cmp	r0, #3
 800d1f4:	d023      	beq.n	0x800d23e
 800d1f6:	2804      	cmp	r0, #4
 800d1f8:	d028      	beq.n	0x800d24c
 800d1fa:	2802      	cmp	r0, #2
 800d1fc:	d116      	bne.n	0x800d22c
 800d1fe:	2004      	movs	r0, #4
 800d200:	f000 fd1c 	bl	0x800dc3c
 800d204:	4604      	mov	r4, r0
 800d206:	b140      	cbz	r0, 0x800d21a
 800d208:	4b12      	ldr	r3, [pc, #72]	@ (0x800d254)
 800d20a:	2201      	movs	r2, #1
 800d20c:	701a      	strb	r2, [r3, #0]
 800d20e:	f000 fd11 	bl	0x800dc34
 800d212:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
 800d216:	f7ff bde0 	b.w	0x800cdda
 800d21a:	4d0f      	ldr	r5, [pc, #60]	@ (0x800d258)
 800d21c:	782b      	ldrb	r3, [r5, #0]
 800d21e:	b133      	cbz	r3, 0x800d22e
 800d220:	f000 fd08 	bl	0x800dc34
 800d224:	2001      	movs	r0, #1
 800d226:	f000 fd17 	bl	0x800dc58
 800d22a:	702c      	strb	r4, [r5, #0]
 800d22c:	bd38      	pop	{r3, r4, r5, pc}
 800d22e:	2001      	movs	r0, #1
 800d230:	f000 fd04 	bl	0x800dc3c
 800d234:	2800      	cmp	r0, #0
 800d236:	d1ea      	bne.n	0x800d20e
 800d238:	2301      	movs	r3, #1
 800d23a:	702b      	strb	r3, [r5, #0]
 800d23c:	e7e9      	b.n	0x800d212
 800d23e:	f000 fcf9 	bl	0x800dc34
 800d242:	2004      	movs	r0, #4
 800d244:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
 800d248:	f000 bd06 	b.w	0x800dc58
 800d24c:	f000 fcf2 	bl	0x800dc34
 800d250:	2001      	movs	r0, #1
 800d252:	e7f7      	b.n	0x800d244
 800d254:	15e9      	asrs	r1, r5, #23
 800d256:	2000      	movs	r0, #0
 800d258:	15e8      	asrs	r0, r5, #23
 800d25a:	2000      	movs	r0, #0
 800d25c:	b538      	push	{r3, r4, r5, lr}
 800d25e:	4604      	mov	r4, r0
 800d260:	b940      	cbnz	r0, 0x800d274
 800d262:	4d05      	ldr	r5, [pc, #20]	@ (0x800d278)
 800d264:	782b      	ldrb	r3, [r5, #0]
 800d266:	b12b      	cbz	r3, 0x800d274
 800d268:	f000 fce4 	bl	0x800dc34
 800d26c:	2004      	movs	r0, #4
 800d26e:	f000 fcf3 	bl	0x800dc58
 800d272:	702c      	strb	r4, [r5, #0]
 800d274:	bd38      	pop	{r3, r4, r5, pc}
 800d276:	bf00      	nop
 800d278:	15e9      	asrs	r1, r5, #23
 800d27a:	2000      	movs	r0, #0
 800d27c:	2805      	cmp	r0, #5
 800d27e:	d80d      	bhi.n	0x800d29c
 800d280:	2905      	cmp	r1, #5
 800d282:	d80b      	bhi.n	0x800d29c
 800d284:	2a11      	cmp	r2, #17
 800d286:	d809      	bhi.n	0x800d29c
 800d288:	236c      	movs	r3, #108	@ 0x6c
 800d28a:	4358      	muls	r0, r3
 800d28c:	2312      	movs	r3, #18
 800d28e:	fb03 0101 	mla	r1, r3, r1, r0
 800d292:	440a      	add	r2, r1
 800d294:	4b02      	ldr	r3, [pc, #8]	@ (0x800d2a0)
 800d296:	f833 0012 	ldrh.w	r0, [r3, r2, lsl #1]
 800d29a:	4770      	bx	lr
 800d29c:	2001      	movs	r0, #1
 800d29e:	4770      	bx	lr
 800d2a0:	69b8      	ldr	r0, [r7, #24]
 800d2a2:	0801      	lsrs	r1, r0, #32
 800d2a4:	f7ff bfea 	b.w	0x800d27c
 800d2a8:	2805      	cmp	r0, #5
 800d2aa:	d808      	bhi.n	0x800d2be
 800d2ac:	b939      	cbnz	r1, 0x800d2be
 800d2ae:	f082 0201 	eor.w	r2, r2, #1
 800d2b2:	4b04      	ldr	r3, [pc, #16]	@ (0x800d2c4)
 800d2b4:	eb02 0040 	add.w	r0, r2, r0, lsl #1
 800d2b8:	f833 0010 	ldrh.w	r0, [r3, r0, lsl #1]
 800d2bc:	4770      	bx	lr
 800d2be:	2001      	movs	r0, #1
 800d2c0:	4770      	bx	lr
 800d2c2:	bf00      	nop
 800d2c4:	69a0      	ldr	r0, [r4, #24]
 800d2c6:	0801      	lsrs	r1, r0, #32
 800d2c8:	f7ff bfee 	b.w	0x800d2a8
